/**
* \file Maze.cpp
* \brief
*
* Depth-first Search Random Maze Generator
*
* \version 1.0.0
* \date 27/05/2014
* \author Sergey Kosarevsky, 2014
* \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
* // Editor: Jacob Tovar
*/

/*
To compile:
	gcc Maze.cpp -std=c++11 -lstdc++
*/

// http://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search

#include "Maze.h"

// return the current index in g_Maze
int Maze::CellIdx()
{
	return g_PtX + NumCells * g_PtY;
}

int Maze::RandomInt()
{
    static std::uniform_int_distribution<> dis( 0, NumCells - 1 );
	return static_cast<int>( dis( gen ) );
}

int Maze::RandomInt4()
{
	return static_cast<int>( dis4( gen ) );
}

////////////////////////////////////////////////////////////////////////////


bool Maze::IsDirValid( eDirection Dir )
{
	int NewX = g_PtX + Heading_X[ Dir ];
	int NewY = g_PtY + Heading_Y[ Dir ];

	if ( !Dir || NewX < 0 || NewY < 0 || NewX >= NumCells || NewY >= NumCells ) return false;

	return !g_Maze[ NewX + NumCells * NewY ];
}

Maze::eDirection Maze::GetDirection()
{
    eDirection Dir = eDirection( 1 << RandomInt4() );

    while ( true )
    {
        for ( int x = 0; x < 4; x++ )
        {
            if ( IsDirValid( Dir ) ) { return eDirection( Dir ); }

            Dir = eDirection( Dir << 1 );

            if ( Dir > eDirection_Left ) { Dir = eDirection_Up; }
        }

        Dir = eDirection( ( g_Maze[ CellIdx() ] & 0xf0 ) >> 4 );

        // nowhere to go
        if ( !Dir ) return eDirection_Invalid;

        g_PtX += Heading_X[ Dir ];
        g_PtY += Heading_Y[ Dir ];

        Dir = eDirection( 1 << RandomInt4() );
    }
}

void Maze::GenerateMaze()
{
	int Cells = 0;

	for ( eDirection Dir = GetDirection(); Dir != eDirection_Invalid; Dir = GetDirection() )
	{
		// a progress indicator, kind of
		if ( ++Cells % 1000 == 0 ) std::cout << ".";

		g_Maze[ CellIdx() ] |= Dir;

		g_PtX += Heading_X[ Dir ];
		g_PtY += Heading_Y[ Dir ];

		g_Maze[ CellIdx() ] = Mask[ Dir ];
	}

    std::cout << std::endl;
}

int Maze::getMazeSize()
{
    return ImageSize;
}

int Maze::getNumCells()
{
    return NumCells;
}


void Maze::Line(unsigned char *img, int x1, int y1, int x2, int y2, std::function<void(double, double, double, double)> OSGcreateWall)
{
    double yCenter{0};
    double yHeight{0};
    double xCenter{0};
    double xWidth{0};
    if ( x1 == x2 )
    {
        // vertical line
        // I think the middle of y1 and y2 is where the center of the box will be in the y direction
        yCenter = (y1+y2)/2;
        yHeight = y2-y1;
        xCenter = (x1+x2)/2;
        xWidth = 10.f;
    }

    if ( y1 == y2 )
    {
        // horizontal line
        xCenter = (x1+x2)/2;
        xWidth = (x2-x1);
        yCenter = (y1+y2)/2;
        yHeight = 10;
    }

    if (xCenter == ImageSize )//&& yCenter==ImageSize-(ImageSize/NumCells))
    {
        xCenter = xCenter*2;
    }

    wall *newWall = new wall(xCenter,yCenter,xWidth,yHeight);
        MazeWallList.push_back(newWall);//new wall(xCenter,yCenter,xWidth,yHeight));
        OSGcreateWall(xCenter,yCenter,xWidth,yHeight);
}

void Maze::RenderMaze(unsigned char *img, std::function<void(double, double, double, double)> OSGcreateWall)
{
    for ( int y = 0; y < NumCells; y++ )
    {
        for ( int x = 0; x < NumCells; x++ )
        {
            char v = g_Maze[ y * NumCells + x ];

            int nx = x * CellSize;
            int ny = y * CellSize;

            if (y == 0 && !( v & eDirection_Up    ) ) Line( img, nx,            ny,            nx + CellSize + 1, ny               ,OSGcreateWall );
            if (/*!(x==NumCells-1) &&*/ !( v & eDirection_Right ) ) Line( img, nx + CellSize, ny,            nx + CellSize,     ny + CellSize + 1,OSGcreateWall );
            if (/*!(y==NumCells-1) &&*/ !( v & eDirection_Down  ) ) Line( img, nx,            ny + CellSize, nx + CellSize + 1, ny + CellSize    ,OSGcreateWall );
            if ( x == 0 && !( v & eDirection_Left  ) ) Line( img, nx,            ny,            nx,                ny + CellSize + 1,OSGcreateWall );
        }
    }
}


/*void Maze::PrintBanner()
{
	std::cout << "Depth-first Search Random Maze Generator" << std::endl;
	std::cout << "Version " << Version << std::endl;
	std::cout << "Sergey Kosarevsky, 2014" << std::endl;
	std::cout << "support@linderdaum.com http://www.linderdaum.com http://blog.linderdaum.com" << std::endl;
	std::cout << std::endl;
	std::cout << "Usage: Maze" << std::endl;
	std::cout << std::endl;
}*/

Maze::Maze() : Maze(1000, 8)
{

}

Maze::Maze(double mazeSize, double cells)
{
    ImageSize = mazeSize;
    NumCells = cells;
    CellSize = ImageSize / NumCells;
    g_Maze = new unsigned char[ NumCells* NumCells ];
}

Maze::~Maze()
{

}

void Maze::MakeMaze(std::function<void(double, double, double, double)> OSGcreateWall)
{
    // prepare PRNG
    gen.seed( time( NULL ) );

    // clear maze
    std::fill( g_Maze, g_Maze + NumCells * NumCells, 0 );

    // setup initial point
    g_PtX = RandomInt();
    g_PtY = RandomInt();

    // traverse
    GenerateMaze();

    // prepare BGR image
    size_t DataSize = 3 * ImageSize * ImageSize;

    unsigned char* Img = new unsigned char[ DataSize ];

    memset( Img, 0, DataSize );

    // render maze on bitmap
    RenderMaze( Img, OSGcreateWall );

    //SaveBMP( "Maze.bmp", Img, ImageSize, ImageSize );

    // cleanup
    delete[]( Img );

}

void Maze::MakeMaze(std::function<void (double, double, double, double)> OSGcreateWall, double mazeSize, double cells)
{
    //Update Maze Parameters
    ImageSize = mazeSize;
    NumCells = static_cast<int>(cells);

    // prepare PRNG
    gen.seed( time( NULL ) );

    // clear maze
    std::fill( g_Maze, g_Maze + NumCells * NumCells, 0 );

    // setup initial point
    g_PtX = RandomInt();
    g_PtY = RandomInt();

    // traverse
    GenerateMaze();

    // prepare BGR image
    size_t DataSize = 3 * ImageSize * ImageSize;

    unsigned char* Img = new unsigned char[ DataSize ];

    memset( Img, 0, DataSize );

    // render maze on bitmap
    RenderMaze( Img, OSGcreateWall );

    //SaveBMP( "Maze.bmp", Img, ImageSize, ImageSize );

    // cleanup
    delete[]( Img );

}


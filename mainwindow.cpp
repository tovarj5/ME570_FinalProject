#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Maze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*
/////////////////// User selectable parameters ///////////////////////////////

//const int ImageSize = 512;
//const int NumCells  = 63;

//////////////////////////////////////////////////////////////////////////////

//const int CellSize = ImageSize / NumCells;
//static OSGWidget graphic{nullptr};

//unsigned char* g_Maze = new unsigned char[ NumCells* NumCells ];

//// current traversing position
//int g_PtX;
//int g_PtY;

//// return the current index in g_Maze
//int CellIdx()
//{
//    return g_PtX + NumCells * g_PtY;
//}

//////////////////////////////////////////////////////////////////////////////

//std::random_device rd;
//std::mt19937 gen( rd() );
//std::uniform_int_distribution<> dis( 0, NumCells - 1 );
//std::uniform_int_distribution<> dis4( 0, 3 );

//int RandomInt()
//{
//    return static_cast<int>( dis( gen ) );
//}

//int RandomInt4()
//{
//    return static_cast<int>( dis4( gen ) );
//}

//////////////////////////////////////////////////////////////////////////////

//enum eDirection
//{
//    eDirection_Invalid = 0,
//    eDirection_Up      = 1,
//    eDirection_Right   = 2,
//    eDirection_Down    = 4,
//    eDirection_Left    = 8
//};

////                   0  1  2  3  4  5  6  7  8
////                      U  R     D           L
//int Heading_X[9] = { 0, 0,+1, 0, 0, 0, 0, 0,-1 };
//int Heading_Y[9] = { 0,-1, 0, 0,+1, 0, 0, 0, 0 };
//int Mask[9]      = {
//                            0,
//                            eDirection_Down | eDirection_Down << 4,
//                            eDirection_Left | eDirection_Left << 4,
//                            0,
//                            eDirection_Up | eDirection_Up << 4,
//                            0,
//                            0,
//                            0,
//                            eDirection_Right | eDirection_Right << 4
//                        };


//////////////////////////////////////////////////////////////////////////////

//bool IsDirValid( eDirection Dir )
//{
//    int NewX = g_PtX + Heading_X[ Dir ];
//    int NewY = g_PtY + Heading_Y[ Dir ];

//    if ( !Dir || NewX < 0 || NewY < 0 || NewX >= NumCells || NewY >= NumCells ) return false;

//    return !g_Maze[ NewX + NumCells * NewY ];
//}

//eDirection GetDirection()
//{
//    eDirection Dir = eDirection( 1 << RandomInt4() );

//    while ( true )
//    {
//        for ( int x = 0; x < 4; x++ )
//        {
//            if ( IsDirValid( Dir ) ) { return eDirection( Dir ); }

//            Dir = eDirection( Dir << 1 );

//            if ( Dir > eDirection_Left ) { Dir = eDirection_Up; }
//        }

//        Dir = eDirection( ( g_Maze[ CellIdx() ] & 0xf0 ) >> 4 );

//        // nowhere to go
//        if ( !Dir ) return eDirection_Invalid;

//        g_PtX += Heading_X[ Dir ];
//        g_PtY += Heading_Y[ Dir ];

//        Dir = eDirection( 1 << RandomInt4() );
//    }
//}

//void GenerateMaze()
//{
//    int Cells = 0;

//    for ( eDirection Dir = GetDirection(); Dir != eDirection_Invalid; Dir = GetDirection() )
//    {
//        // a progress indicator, kind of
//        if ( ++Cells % 1000 == 0 ) std::cout << ".";

//        g_Maze[ CellIdx() ] |= Dir;

//        g_PtX += Heading_X[ Dir ];
//        g_PtY += Heading_Y[ Dir ];

//        g_Maze[ CellIdx() ] = Mask[ Dir ];
//    }

//    std::cout << std::endl;
//}

///*#if defined( __GNUC__ )
//# define GCC_PACK(n) __attribute__((packed,aligned(n)))
//#else
//# define GCC_PACK(n) __declspec(align(n))
//#endif // __GNUC__

//#pragma pack(push, 1)
//struct GCC_PACK( 1 ) sBMPHeader
//{
//    // BITMAPFILEHEADER
//    unsigned short bfType;
//    uint32_t bfSize;
//    unsigned short bfReserved1;
//    unsigned short bfReserved2;
//    uint32_t bfOffBits;
//    // BITMAPINFOHEADER
//    uint32_t biSize;
//    uint32_t biWidth;
//    uint32_t biHeight;
//    unsigned short biPlanes;
//    unsigned short biBitCount;
//    uint32_t biCompression;
//    uint32_t biSizeImage;
//    uint32_t biXPelsPerMeter;
//    uint32_t biYPelsPerMeter;
//    uint32_t biClrUsed;
//    uint32_t biClrImportant;
//};
//#pragma pack(pop)*/

///*void SaveBMP( const char* FileName, const void* RawBGRImage, int Width, int Height )
//{
//    sBMPHeader Header;

//    int ImageSize = Width * Height * 3;

//    Header.bfType = 0x4D * 256 + 0x42;
//    Header.bfSize = ImageSize + sizeof( sBMPHeader );
//    Header.bfReserved1 = 0;
//    Header.bfReserved2 = 0;
//    Header.bfOffBits = 0x36;
//    Header.biSize = 40;
//    Header.biWidth = Width;
//    Header.biHeight = Height;
//    Header.biPlanes = 1;
//    Header.biBitCount = 24;
//    Header.biCompression = 0;
//    Header.biSizeImage = ImageSize;
//    Header.biXPelsPerMeter = 6000;
//    Header.biYPelsPerMeter = 6000;
//    Header.biClrUsed = 0;
//    Header.biClrImportant = 0;

//    std::ofstream File( FileName, std::ios::out | std::ios::binary );

//    File.write( ( const char* )&Header, sizeof( Header ) );
//    File.write( ( const char* )RawBGRImage, ImageSize );

//    std::cout << "Saved " << FileName << std::endl;
//}*/

//void Line( unsigned char* img, int x1, int y1, int x2, int y2 )
//{
//    double yCenter{0};
//    double yHeight{0};
//    double xCenter{0};
//    double xWidth{0};
//    if ( x1 == x2 )
//    {
//        // vertical line
//        // I think the middle of y1 and y2 is where the center of the box will be in the y direction
//        yCenter = (y1+y2)/2;
//        yHeight = y2-y1;
//        xCenter = (x1+x2)/2;
//        xWidth = 10.f;
//        graphic.create_wall(xCenter,yCenter,xWidth,yHeight);
////        for ( int y = y1; y < y2; y++ )
////		{
////			if ( x1 >= ImageSize || y >= ImageSize ) continue;
////			int i = 3 * ( y * ImageSize + x1 );
////            // i is where the center box in the x direction will be
////			img[ i + 2 ] = img[ i + 1 ] = img[ i + 0 ] = 255;
////		}
//    }

//    if ( y1 == y2 )
//    {
//        // horizontal line
//        xCenter = (x1+x2)/2;
//        xWidth = (x2-x1);
//        yCenter = (y1+y2)/2;
//        yHeight = 10;
//        graphic.create_wall(xCenter,yCenter,xWidth,yHeight);
////		for ( int x = x1; x < x2; x++ )
////		{
////			if ( y1 >= ImageSize || x >= ImageSize ) continue;
////			int i = 3 * ( y1 * ImageSize + x );
////			img[ i + 2 ] = img[ i + 1 ] = img[ i + 0 ] = 255;
////		}
//    }
//}

//void RenderMaze( unsigned char* img )
//{
//    for ( int y = 0; y < NumCells; y++ )
//    {
//        for ( int x = 0; x < NumCells; x++ )
//        {
//            char v = g_Maze[ y * NumCells + x ];

//            int nx = x * CellSize;
//            int ny = y * CellSize;

//            if ( !( v & eDirection_Up    ) ) Line( img, nx,            ny,            nx + CellSize + 1, ny                );
//            if ( !( v & eDirection_Right ) ) Line( img, nx + CellSize, ny,            nx + CellSize,     ny + CellSize + 1 );
//            if ( !( v & eDirection_Down  ) ) Line( img, nx,            ny + CellSize, nx + CellSize + 1, ny + CellSize     );
//            if ( !( v & eDirection_Left  ) ) Line( img, nx,            ny,            nx,                ny + CellSize + 1 );
//        }
//    }
//}


///*void PrintBanner()
//{
//    std::cout << "Depth-first Search Random Maze Generator" << std::endl;
//    std::cout << "Version " << Version << std::endl;
//    std::cout << "Sergey Kosarevsky, 2014" << std::endl;
//    std::cout << "support@linderdaum.com http://www.linderdaum.com http://blog.linderdaum.com" << std::endl;
//    std::cout << std::endl;
//    std::cout << "Usage: Maze" << std::endl;
//    std::cout << std::endl;
//}*/

//void MakeMaze()
//{
//    //graphic = wid;
//    //PrintBanner();

//    //std::cout << "Generating " << NumCells << " x " << NumCells << " maze into " << ImageSize << " x " << ImageSize << " bitmap" << std::endl;

//    // prepare PRNG
//    gen.seed( time( NULL ) );

//    // clear maze
//    std::fill( g_Maze, g_Maze + NumCells * NumCells, 0 );

//    // setup initial point
//    g_PtX = RandomInt();
//    g_PtY = RandomInt();

//    // traverse
//    GenerateMaze();

//    // prepare BGR image
//    size_t DataSize = 3 * ImageSize * ImageSize;

//    unsigned char* Img = new unsigned char[ DataSize ];

//    memset( Img, 0, DataSize );

//    // render maze on bitmap
//    RenderMaze( Img );

//    //SaveBMP( "Maze.bmp", Img, ImageSize, ImageSize );

//    // cleanup
//    delete[]( Img );

//}


void MainWindow::on_actionStart_New_Game_triggered()
{
    on_actionClear_Maze_triggered();

    double x{0},y{0},z{0},w{0};
    ui->osgGraphicWidget->create_wall(x,y,z,w);
    Maze *m = new Maze;

    m->MakeMaze([this](double a, double b, double c, double d)
    {
        ui->osgGraphicWidget->create_wall(a, b, c, d);
    });
}

void MainWindow::on_actionClear_Maze_triggered()
{
   ui->osgGraphicWidget->clear();
   ui->osgGraphicWidget->update();
//   ui->osgGraphicWidget->create_outerWalls();
}

void MainWindow::on_actionBouncy_Ball_Example_triggered()
{

}

void MainWindow::on_actionMaze_Settings_triggered()
{

}

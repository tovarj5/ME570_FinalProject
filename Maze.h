#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <fstream>
#include <random>
#include <functional>
#include <osg/MatrixTransform>

class OSGWidget;

class Maze
{
private:

    enum eDirection
    {
        eDirection_Invalid = 0,
        eDirection_Up      = 1,
        eDirection_Right   = 2,
        eDirection_Down    = 4,
        eDirection_Left    = 8
    };
    struct wall
    {
        double mXcenter{0};
        double mYCenter{0};
        double mXwidth{0};
        double mYheight{0};
        wall(double xc,double yc, double xw,double yh)
        {
            mXcenter = xc;
            mYCenter = yc;
            mXwidth = xw;
            mYheight = yh;
        }
    };

    std::list<wall*> MazeWallList;

///////////////// User selectable parameters ///////////////////////////////

 int ImageSize = 500*2;
 int NumCells  = 100/(12);

////////////////////////////////////////////////////////////////////////////

const char* Version = "1.0.0 (27/05/2014)";

int CellSize;// = ImageSize / NumCells;

unsigned char* g_Maze;// = new unsigned char[ NumCells* NumCells ];

// current traversing position
int g_PtX;
int g_PtY;

std::random_device rd;
std::mt19937 gen{ rd() };
std::uniform_int_distribution<> dis4{ 0, 3 };

////////////////////////////////////////////////////////////////////////////

//                   0  1  2  3  4  5  6  7  8
//                      U  R     D           L
int Heading_X[9] = { 0, 0,+1, 0, 0, 0, 0, 0,-1 };
int Heading_Y[9] = { 0,-1, 0, 0,+1, 0, 0, 0, 0 };
int Mask[9]      = {
                            0,
                            eDirection_Down | eDirection_Down << 4,
                            eDirection_Left | eDirection_Left << 4,
                            0,
                            eDirection_Up | eDirection_Up << 4,
                            0,
                            0,
                            0,
                            eDirection_Right | eDirection_Right << 4
                        };


////////////////////////////////////////////////////////////////////////////


void Line( unsigned char* img, int x1, int y1, int x2, int y2, std::function<void(double, double, double, double)> OSGcreateWall);
void RenderMaze(unsigned char* img , std::function<void(double, double, double, double)> OSGcreateWall);
eDirection GetDirection();
bool IsDirValid( eDirection Dir );
int RandomInt4();
int RandomInt();
int CellIdx();


public:
Maze();
Maze(double mazeSize, double cells);
~Maze();
void MakeMaze();
void MakeMaze(std::function<void(double, double, double, double)> OSGcreateWall);
void MakeMaze(std::function<void(double, double, double, double)> OSGcreateWall, double mazeSize, double cells);
void GenerateMaze();
int getMazeSize();
//void setMazeSize(int siz);
int getNumCells();
//void setNumCells(int num);
};

#endif

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
#include "mainwindow.h"
#include <functional>

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

//void SaveBMP( const char* FileName, const void* RawBGRImage, int Width, int Height );

///////////////// User selectable parameters ///////////////////////////////

const int ImageSize = 500*2;
const int NumCells  = 63/4;

////////////////////////////////////////////////////////////////////////////

const char* Version = "1.0.0 (27/05/2014)";

const int CellSize = ImageSize / NumCells;
//OSGWidget graphic{nullptr};
unsigned char* g_Maze = new unsigned char[ NumCells* NumCells ];

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


void Line( unsigned char* img, int x1, int y1, int x2, int y2 );
void Line( unsigned char* img, int x1, int y1, int x2, int y2, std::function<void(double, double, double, double)> OSGcreateWall);
void RenderMaze( unsigned char* img );
void RenderMaze(unsigned char* img , std::function<void(double, double, double, double)> OSGcreateWall);
eDirection GetDirection();
bool IsDirValid( eDirection Dir );
int RandomInt4();
int RandomInt();
int CellIdx();
void PrintBanner();

public:
Maze();
void MakeMaze();
void MakeMaze(std::function<void(double, double, double, double)> OSGcreateWall);
void GenerateMaze();
};

#endif

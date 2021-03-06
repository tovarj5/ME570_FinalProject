#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <fstream>
#include <random>
#include "osgwidget.h"
#include "Maze.h"
#include <QMessageBox>
#include <btBulletDynamicsCommon.h>
#include<btBulletCollisionCommon.h>
#include <Bullet3Common/b3AlignedAllocator.h>
#include <QKeyEvent>
#include <vector>
#include "instructionsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //QEvent::KeyPress(QKeyEvent *event);
    //QEvent::KeyRelease(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
//    void keyPressEvent(QKeyEvent* event);

    void on_actionStart_New_Game_triggered();

    void on_actionClear_Maze_triggered();

    void on_actionBouncy_Ball_Example_triggered();

    void on_actionMaze_Settings_triggered();

    void on_actionPrint_Wall_List_triggered();

    void on_actionShow_Instructions_triggered();

private:
    Ui::MainWindow *ui;
    int mPlayer2Index{0};
    instructionsdialog * minstructions{nullptr};
    Maze *mMazeObj{nullptr};
    double mMazeSize{500*2};
    double mNumCells{20};
    bool mazeGenerated{false};
    int moves{0};
    int maxMoves{5};
    std::vector<double> mpresetMaze{500,1000,1500,2000,2500,3000};
    std::vector<double> mpresetCells{10,16.7,20,30,40,50};
    //struct settings

        int mDifficulty{1};
        int mPlayers{1};
        bool mSolidWalls{true};
        //double mMazeSize{1000};
        float mWallRebound{0.1};


    struct Box
    {
        double xCenter{0};
        double yCenter{0};
        double xWidth{0};
        double yHeight{0};
    };
};

#endif // MAINWINDOW_H

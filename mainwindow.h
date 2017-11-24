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
    void keyPressEvent(QKeyEvent* event);

    void on_actionStart_New_Game_triggered();

    void on_actionClear_Maze_triggered();

    void on_actionBouncy_Ball_Example_triggered();

    void on_actionMaze_Settings_triggered();

private:
    Ui::MainWindow *ui;
    //Maze *mazeObj{nullptr};
    struct Box
    {
        double xCenter{0};
        double yCenter{0};
        double xWidth{0};
        double yHeight{0};
    };
};

#endif // MAINWINDOW_H

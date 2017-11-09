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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionStart_New_Game_triggered();

private:
    Ui::MainWindow *ui;
    struct Box
    {
        double xCenter{0};
        double yCenter{0};
        double xWidth{0};
        double yHeight{0};
    };
};

#endif // MAINWINDOW_H

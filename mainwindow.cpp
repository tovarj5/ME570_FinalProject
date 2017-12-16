#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Maze.h"
#include "settingswindow.h"
#include "getkeycode.h"
#include "btBulletDynamicsCommon.h"
#include "QDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    instructionsdialog *instruct = new instructionsdialog;
    minstructions = instruct;
}

MainWindow::~MainWindow()
{
    delete minstructions;
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Check that the key event applies to these functions
    if (event->type() == QEvent::KeyPress && mazeGenerated && obj->objectName()=="osgGraphicWidget")
       {
        //Check is the player has won or not.
        if(ui->osgGraphicWidget->checkPlayerWin())
        {
            QMessageBox *msgbox = new QMessageBox;
            msgbox->setText(QString("Player Wins!"));
            msgbox->show();
            mNumCells = static_cast<int>(mNumCells*1.10);
//            if(mNumCells == 13 ||mNumCells ==11||mNumCells ==9 ||mNumCells ==7 || mNumCells ==4)
//            {
//                mNumCells  = mNumCells +1;
//            }
            //ui->osgGraphicWidget->moveBall(btVector3(0,0,1000));
            ui->PlayerLineEdit->setText(QString::number((ui->PlayerLineEdit->text().toInt())+1));
            on_actionStart_New_Game_triggered();
            return QObject::eventFilter(obj, event);
        }

           QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
              qDebug() << "key " << keyEvent->key() << "from" << obj;

              QMessageBox *msgbox = new QMessageBox;
              btVector3 currentVelocity{ui->osgGraphicWidget->getRigidBodyVelocity()};
              btVector3 velocity{0,0,0};
              float addSpeed{500.0};
              if(keyEvent->key()==Qt::Key_Up)
              {
                  velocity = {0,addSpeed,0};
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Down)
              {
                  velocity={0,-addSpeed,0};
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Left)
              {
                  velocity={-addSpeed,0,0};
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Right)
              {
                  velocity= {addSpeed,0,0};
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
   /*           else if(keyEvent->key()==Qt::Key_0)
              {
//                  msgbox->setText(QString("Right"));
                  velocity={0,0,-addSpeed};
//                  velocity = currentVelocity+velocity;
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }*/
              else if(keyEvent->key()==Qt::Key_9 && mNumCells ==12)
              {
                  velocity={0,0,addSpeed};
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }

              //For Demonstration purposes
              else if (keyEvent->key() == Qt::Key_Z)
              {
                  mNumCells = mNumCells*1.1;

                  on_actionStart_New_Game_triggered();
                  keyEvent->accept();

              }
              //Keys to move the walls
              else if(keyEvent->key()==Qt::Key_1 && mPlayer2Index >1)
              {
                  moves=0;
                  mPlayer2Index = mPlayer2Index-1;
                  ui->osgGraphicWidget->nextWall(mPlayer2Index);
                  keyEvent->accept();
              }
              else if (keyEvent->key()==Qt::Key_3)
              {
                  moves =0;
                  mPlayer2Index = mPlayer2Index +1;
                  ui->osgGraphicWidget->nextWall(mPlayer2Index);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Q)
              {
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallDown();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_W)
              {
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallDown();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_E)
              {
                  //move wall right in the x direction
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallUp();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_2)
              {
                  //Move wall up in the y direction
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallUp();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_4)
              {
                  int High{static_cast<int>(ui->osgGraphicWidget->getWallList().size())},Low{0};
                  int  finishLocX{qrand() % ((High + 1) - Low) + Low};
//                  int finishLocY{qrand() % ((High + 1) - Low) + Low};
                  mPlayer2Index = finishLocX;
                  ui->osgGraphicWidget->nextWall(mPlayer2Index);
                  //Delete selected wall
                  keyEvent->accept();
              }


              //If the space bar is pressed, generate a new maze and increase the Maze Players points.
              if(keyEvent->key()==Qt::Key_Space)
              {
                  //Save player location
                  mNumCells = static_cast<int>(mNumCells/1.1);
                  if(mNumCells <14)
                      mNumCells =12;

                  ui->MazeLineEdit->setText(QString::number((ui->MazeLineEdit->text().toInt()+1)));
                  on_actionStart_New_Game_triggered();
                  //transform player back to location.
                  keyEvent->accept();
                  if (mNumCells==12)
                  {
                      msgbox->setText(QString("Ball Player can use key 9 to jump!"));
                      msgbox->show();
                  }

              }
              ui->osgGraphicWidget->update();

       }
       return QObject::eventFilter(obj, event);
}

void MainWindow::on_actionStart_New_Game_triggered()
{
    on_actionClear_Maze_triggered();

//    if(!(static_cast<int>(mMazeSize) % static_cast<int>(mNumCells) ==0))
//    {
//        mMazeSize = static_cast<int>(mMazeSize/mNumCells)*mNumCells;
//    }
    Maze *m = new Maze(mMazeSize,mNumCells);
    double player{static_cast<double>(m->getMazeSize()/(m->getNumCells()*2))};
    ui->osgGraphicWidget->create_player(player,player,player/2);
    ui->osgGraphicWidget->create_ground(osg::Vec3(mMazeSize/2,mMazeSize/2,5),mMazeSize);
    ui->osgGraphicWidget->create_outerWalls(mMazeSize);
    ui->osgGraphicWidget->create_cone(mMazeSize);
    ui->osgGraphicWidget->update();

    m->MakeMaze([this](double a, double b, double c, double d)
    {
        ui->osgGraphicWidget->create_wall(a, b, c, d);
    });//,mMazeSize,mNumCells);
    mMazeObj = m;
    mazeGenerated = true;
    ui->osgGraphicWidget->start_timer();

    //Check that a grid wasn't created
//    std::list<bulletWall*> list{ui->osgGraphicWidget->getWallList()};
//    int i{0};
//    for (bulletWall *wall : list)
//    {
//        i++;
//    }
//    if(i > 300 && mNumCells == 12)
//        on_actionStart_New_Game_triggered();
}

void MainWindow::on_actionClear_Maze_triggered()
{
//   delete mMazeObj;

   ui->osgGraphicWidget->clear();
   ui->osgGraphicWidget->update();
   mazeGenerated = false;
//   ui->osgGraphicWidget->create_outerWalls();
}

void MainWindow::on_actionBouncy_Ball_Example_triggered()
{
    ui->osgGraphicWidget->setup_single_ball(osg::Vec3(mMazeSize/2,mMazeSize/2,5),mMazeSize);
    ui->osgGraphicWidget->start_timer();
}

void MainWindow::on_actionMaze_Settings_triggered()
{
    double mSize{1000}, cellSize{0}, wallLength{0}, restitution{0};
    int difficulty{1};
    std::vector<double> mazeSettings;
    settingswindow *settings = new settingswindow();
    settings->exec();

    mazeSettings = settings->getSettings();


    mMazeSize = settings->getMazeSize();
    mNumCells = settings->getCellSize();
    QMessageBox *msgbox = new QMessageBox;
    //msgbox->setText(QString::number(mazeSize) + "|"+ QString::number(mazeCells));
    msgbox->setText(QString::number(mazeSettings[0]));
    msgbox->show();
}


void MainWindow::on_actionPrint_Wall_List_triggered()
{
    QMessageBox *msgbox = new QMessageBox;
    std::list<bulletWall*> list{ui->osgGraphicWidget->getWallList()};
    QString message{""};
    int i{0};
    for (bulletWall *wall : list)
    {
        i++;
        message.append(QString::number(i)+"|");
    }
    msgbox->setText(message);
    msgbox->show();
}

void MainWindow::on_actionShow_Instructions_triggered()
{
    minstructions->show();
}

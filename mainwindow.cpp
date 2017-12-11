#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Maze.h"
#include "settingswindow.h"
#include "getkeycode.h"
#include "btBulletDynamicsCommon.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && mazeGenerated && obj->objectName()=="osgGraphicWidget")
       {
        if(ui->osgGraphicWidget->checkPlayerWin())
        {
            QMessageBox *msgbox = new QMessageBox;
            msgbox->setText(QString("Player Wins!"));
            msgbox->show();
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
//                  msgbox->setText(QString("UP"));
                  velocity = {0,addSpeed,0};
//                  velocity = currentVelocity+velocity;
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Down)
              {
//                  msgbox->setText(QString("Down"));
                  velocity={0,-addSpeed,0};
//                  velocity = currentVelocity+velocity;
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Left)
              {
//                  msgbox->setText(QString("Left"));
                  velocity={-addSpeed,0,0};
//                  velocity = currentVelocity+velocity;
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_Right)
              {
//                  msgbox->setText(QString("Right"));
                  velocity= {addSpeed,0,0};
//                  velocity = currentVelocity+velocity;
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_0)
              {
//                  msgbox->setText(QString("Right"));
                  velocity={0,0,-addSpeed};
//                  velocity = currentVelocity+velocity;
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
              else if(keyEvent->key()==Qt::Key_9)
              {
//                  msgbox->setText(QString("Right"));
                  velocity={0,0,addSpeed};
                  ui->osgGraphicWidget->moveBall(velocity);
                  keyEvent->accept();
              }
//              else{}

              else if(keyEvent->key()==Qt::Key_Q)
              {
                  moves=0;
                  mPlayer2Index = mPlayer2Index-1;
                  ui->osgGraphicWidget->nextWall(mPlayer2Index);
                  keyEvent->accept();
              }
              else if (keyEvent->key()==Qt::Key_E)
              {
                  moves =0;
                  mPlayer2Index = mPlayer2Index +1;
                  ui->osgGraphicWidget->nextWall(mPlayer2Index);
                  keyEvent->accept();
                  /*QMessageBox *msgbox = new QMessageBox;
                  double *xC{nullptr},*yC{nullptr};
                  ui->osgGraphicWidget->getCurrentWallDim(xC,yC);
                  msgbox->setText(QString("X: ") + QString::number(*xC) + QString("|Y: ") + *///QString::number(*yC));
              }
              else if(keyEvent->key()==Qt::Key_A)
              {
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallDown();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_X)
              {
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallDown();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_D)
              {
                  //move wall right in the x direction
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallUp();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_W)
              {
                  //Move wall up in the y direction
                  if(moves <maxMoves)
                  {
                      moves++;
                      ui->osgGraphicWidget->moveWallUp();
                      keyEvent->accept();
                  }
              }
              else if(keyEvent->key()==Qt::Key_Z)
              {
                  int High{static_cast<int>(ui->osgGraphicWidget->getWallList().size())},Low{0};
                  int  finishLocX{qrand() % ((High + 1) - Low) + Low};
//                  int finishLocY{qrand() % ((High + 1) - Low) + Low};
                  mPlayer2Index = finishLocX;
                  ui->osgGraphicWidget->nextWall(mPlayer2Index);
                  //Delete selected wall
                  keyEvent->accept();
              }
              else
              {}

              if(keyEvent->key()==Qt::Key_Space)
              {
                  //Save player location

                  ui->MazeLineEdit->setText(QString::number((ui->MazeLineEdit->text().toInt()+1)));
                  on_actionStart_New_Game_triggered();
                  //transform player back to location.
                  keyEvent->accept();

              }
              ui->osgGraphicWidget->update();
//              int maxVel{300};
//              if(velocity[0]<maxVel || velocity[1]<maxVel ||velocity[2]<maxVel)
                  //velocity = currentVelocity+velocity;

//              ui->osgGraphicWidget->moveBall(velocity);
//                  msgbox->show();
       }
       return QObject::eventFilter(obj, event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMessageBox *msgbox = new QMessageBox;
    msgbox->setText(QString("KeyPressed"));
    msgbox->show();

    if(event->key()==Qt::Key_Up)
    {
        msgbox->setText(QString("UP"));
        btVector3 velocity{0,100,0};
        ui->osgGraphicWidget->moveBall(velocity);
    }
    else if(event->key()==Qt::Key_Down)
    {
        msgbox->setText(QString("Down"));
        btVector3 velocity{0,-100,0};
        ui->osgGraphicWidget->moveBall(velocity);
    }
    else if(event->key()==Qt::Key_Left)
    {
        msgbox->setText(QString("Left"));
        btVector3 velocity{-100,0,0};
        ui->osgGraphicWidget->moveBall(velocity);
    }
    else if(event->key()==Qt::Key_Right)
    {
        msgbox->setText(QString("Right"));
        btVector3 velocity{100,0,0};
        ui->osgGraphicWidget->moveBall(velocity);
    }

    else if (event->key()==Qt::Key_0)
    {
        btVector3 velocity{0,0,300};
        ui->osgGraphicWidget->moveBall(velocity);
    }
    msgbox->show();

}


void MainWindow::on_actionStart_New_Game_triggered()
{
    on_actionClear_Maze_triggered();

//    double x{0},y{0},z{0},w{0};
  //  ui->osgGraphicWidget->create_wall(x,y,z,w);
    Maze *m = new Maze;
    double player{static_cast<double>(m->getMazeSize()/(m->getNumCells()*2))};
    ui->osgGraphicWidget->create_player(player,player,player/2);
    ui->osgGraphicWidget->create_ground(osg::Vec3(mMazeSize/2,mMazeSize/2,5),mMazeSize);
    ui->osgGraphicWidget->create_outerWalls(mMazeSize);
    ui->osgGraphicWidget->create_cone(mMazeSize);
    ui->osgGraphicWidget->update();

    m->MakeMaze([this](double a, double b, double c, double d)
    {
        ui->osgGraphicWidget->create_wall(a, b, c, d);
    },mMazeSize,mNumCells);

    mazeGenerated = true;
    //mazeObj = m;
    ui->osgGraphicWidget->start_timer();
}

void MainWindow::on_actionClear_Maze_triggered()
{
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

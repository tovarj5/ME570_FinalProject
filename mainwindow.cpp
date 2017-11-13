#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Maze.h"
#include "settingswindow.h"

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

/*void Line( unsigned char* img, int x1, int y1, int x2, int y2 )
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
        graphic.create_wall(xCenter,yCenter,xWidth,yHeight);
//        for ( int y = y1; y < y2; y++ )
//		{
//			if ( x1 >= ImageSize || y >= ImageSize ) continue;
//			int i = 3 * ( y * ImageSize + x1 );
//            // i is where the center box in the x direction will be
//			img[ i + 2 ] = img[ i + 1 ] = img[ i + 0 ] = 255;
//		}
    }

    if ( y1 == y2 )
    {
        // horizontal line
        xCenter = (x1+x2)/2;
        xWidth = (x2-x1);
        yCenter = (y1+y2)/2;
        yHeight = 10;
        graphic.create_wall(xCenter,yCenter,xWidth,yHeight);
//		for ( int x = x1; x < x2; x++ )
//		{
//			if ( y1 >= ImageSize || x >= ImageSize ) continue;
//			int i = 3 * ( y1 * ImageSize + x );
//			img[ i + 2 ] = img[ i + 1 ] = img[ i + 0 ] = 255;
//		}
    }
}

void RenderMaze( unsigned char* img )
{
    for ( int y = 0; y < NumCells; y++ )
    {
        for ( int x = 0; x < NumCells; x++ )
        {
            char v = g_Maze[ y * NumCells + x ];

            int nx = x * CellSize;
            int ny = y * CellSize;

            if ( !( v & eDirection_Up    ) ) Line( img, nx,            ny,            nx + CellSize + 1, ny                );
            if ( !( v & eDirection_Right ) ) Line( img, nx + CellSize, ny,            nx + CellSize,     ny + CellSize + 1 );
            if ( !( v & eDirection_Down  ) ) Line( img, nx,            ny + CellSize, nx + CellSize + 1, ny + CellSize     );
            if ( !( v & eDirection_Left  ) ) Line( img, nx,            ny,            nx,                ny + CellSize + 1 );
        }
    }
}*/

/*void MakeMaze()
{
    //graphic = wid;
    //PrintBanner();

    //std::cout << "Generating " << NumCells << " x " << NumCells << " maze into " << ImageSize << " x " << ImageSize << " bitmap" << std::endl;

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
    RenderMaze( Img );

    //SaveBMP( "Maze.bmp", Img, ImageSize, ImageSize );

    // cleanup
    delete[]( Img );

}*/

/*void bullet()
{
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

            btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
            btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

            btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

            btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

            dynamicsWorld->setGravity(btVector3(0, -10, 0));


            btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

            btCollisionShape* fallShape = new btSphereShape(1);


            btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
            btRigidBody::btRigidBodyConstructionInfo
                    groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
            btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
            dynamicsWorld->addRigidBody(groundRigidBody);


            btDefaultMotionState* fallMotionState =
                    new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
            btScalar mass = 1;
            btVector3 fallInertia(0, 0, 0);
            fallShape->calculateLocalInertia(mass, fallInertia);
            btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
            btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
            dynamicsWorld->addRigidBody(fallRigidBody);


            for (int i = 0; i < 300; i++) {
                    dynamicsWorld->stepSimulation(1 / 60.f, 10);

                    btTransform trans;
                    fallRigidBody->getMotionState()->getWorldTransform(trans);

                    std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
            }

            dynamicsWorld->removeRigidBody(fallRigidBody);
            delete fallRigidBody->getMotionState();
            delete fallRigidBody;

            dynamicsWorld->removeRigidBody(groundRigidBody);
            delete groundRigidBody->getMotionState();
            delete groundRigidBody;


            delete fallShape;

            delete groundShape;


            delete dynamicsWorld;
            delete solver;
            delete collisionConfiguration;
            delete dispatcher;
            delete broadphase;
}*/


void MainWindow::on_actionStart_New_Game_triggered()
{
    on_actionClear_Maze_triggered();

    double x{0},y{0},z{0},w{0};
    ui->osgGraphicWidget->create_wall(x,y,z,w);
    Maze *m = new Maze;
    double player{m->getMazeSize()/(m->getNumCells()*2)};
    ui->osgGraphicWidget->create_player(player,player,player/2);

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
    settingswindow *settings = new settingswindow;
    settings->show();
}

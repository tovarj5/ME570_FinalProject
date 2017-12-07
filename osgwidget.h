//  ***********************************
//  This class is a used to display 
//  Openscenegraph in a Qt window.
//  
//  This is based upon the work of
//  https://github.com/Submanifold/QtOSG.git
//
//  The was created for
//  MEEN / CEEN 570 - Brigham Young University
//  by Prof. Corey McBride
//  ***********************************


#ifndef MEEN_570_OSGWIDGET
#define MEEN_570_OSGWIDGET

#include <QOpenGLWidget>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>

#include <btBulletDynamicsCommon.h>
#include "BouncyBall.h"
#include "ground.h"
#include "bulletWall.h"


class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();
//  void create_shape( Shape *s);
//  void delete_shape(int id);
//  void create_box(Box *b);
//  void create_box(double h,double w,double d);
  void create_triangle();
//  void create_ellipsoid(Ellipsoid *e);
  void create_player(double xCenter,double yCenter,double radius);
  void create_cone(double mazeSize);//Cone *c);// double h, double radx,double rady);
  void clear();
  void remove_shape(int index);
  void create_wall(double xCenter,double yCenter,double xWidth,double yHeight);
  void create_outerWalls(double MazeSize);

  //Bullet Function Calls
  void start_timer();
  void stop_timer();
  void setup_single_ball(osg::Vec3 groundPos, double groundSize);
  void reset_world();
  void moveBall(btVector3 velocity);
  btVector3 getRigidBodyVelocity();
  void nextWall(int index);
  void moveWallDown();
  void moveWallUp();
  void create_ground(osg::Vec3 groundPos,double groundSize);
  void deleteWall();
  bool checkPlayerWin();
  std::list<bulletWall*> getWallList();
  void getCurrentWallDim(double *yCenter, double *xCenter);

protected:

  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );
  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );
  virtual void mouseMoveEvent( QMouseEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void wheelEvent( QWheelEvent* event );
  virtual bool event( QEvent* event );
  void timerEvent(QTimerEvent *);

private:
  void Setup_Viewer();
  void create_box1();
  void create_box2();
  void create_box3();


  virtual void go_home();
  virtual void on_resize( int width, int height );

  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
  osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
  osg::ref_ptr<osg::Group> mRoot;
  osg::ref_ptr<osgGA::TrackballManipulator> mManipulator;

  //Bullet Private Variables.
  btBroadphaseInterface* mBroadphaseInterface;
  btDefaultCollisionConfiguration* mDefaultCollisionConfig;
  btCollisionDispatcher* mCollisionDispatcher;
  btSequentialImpulseConstraintSolver* mSeqImpConstraintSolver;
  btDiscreteDynamicsWorld* mDynamicsWorld;

  double mTimeStep;
  bool mStarted;
  int mTimerId{0};

  Ground* mGround;
  bulletWall *mWall;
  BouncyBall* mBouncyBall {nullptr};
  void initPhysics();
  void createWorld();
  bulletWall *currentSelectedWall;
  std::vector<double> mfinishPos{0,0,0};

  osg::Timer_t mStartTick;
  int mIndex{0};
  bool mBusy;
  std::list<bulletWall*> mplayer2WallList;
  std::set<bulletWall*> wallSet;
};

#endif

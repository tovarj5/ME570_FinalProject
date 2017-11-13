#include "osgwidget.h"

#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>

#include <cassert>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>


OSGWidget::OSGWidget( QWidget* parent, Qt::WindowFlags f ):
    QOpenGLWidget( parent,f ),
    mGraphicsWindow{ new osgViewer::GraphicsWindowEmbedded( this->x(),
                                                            this->y(),
                                                            this->width(),
                                                            this->height() ) }
  , mViewer{ new osgViewer::CompositeViewer }
{

    mRoot = new osg::Group;

    //create_box(2.0,2.0,2.0);
    //create_triangle();
    //create_cone();
    //create_ellipsoid();
    Setup_Viewer();

    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
    auto pixelRatio   = this->devicePixelRatio();

    //Set up the camera
    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width() * pixelRatio, this->height() * pixelRatio );

    camera->setClearColor( osg::Vec4( 0.8f, 0.8f,0.8f, 1.f ) );
    camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( mGraphicsWindow );

    //Set up the view
    osgViewer::View* view = new osgViewer::View;
    view->setCamera( camera );
    view->setSceneData( mRoot.get() );
    view->addEventHandler( new osgViewer::StatsHandler );

    //Set up the mouse control
    mManipulator = new osgGA::TrackballManipulator;
    mManipulator->setAllowThrow( false );

    view->setCameraManipulator( mManipulator );
    mManipulator->setTransformation(osg::Vec3d(2,0,0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));

    mViewer->addView( view );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();

    // Set the focus policy so that this widget will recieve keyboard events.
    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );

    // This allows this widget to get mouse move events.
    // This is needed with multiple view ports.
    this->setMouseTracking( true );

    //Reset the camera
    go_home();
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::Setup_Viewer()
{
    osg::Sphere *sphere = new osg::Sphere(osg::Vec3(0,0,0),1.f);
    osg::ShapeDrawable *sd = new osg::ShapeDrawable(sphere);

    //sd->setColor(osg::Vec4(1.0f,0.f,0.f,1.f));
    sd->setColor(osg::Vec4(1.0f,0.f,1.f,1.f));
    sd->setName("Ellipsoid1");

    osg::Geode *geode = new osg::Geode;
    geode->addDrawable(sd);

    // Set material for basic lighting and enable depth tests. Else, the box
    // will suffer from rendering errors.
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


    //Set up transform parent node.
//    osg::MatrixTransform* transform= new osg::MatrixTransform;
//    transform->setMatrix(osg::Matrix::translate(cx,cy,cz));
    osg::MatrixTransform* transform = new osg::MatrixTransform;
// //   osg::Matrix matrix = osg::Matrix::rotate(osg::DegreesToRadians((float)90),1,0,0);
//    osg::Matrix siz = osg::Matrix::scale(radx,rady,radz);
    osg::Matrix trans = osg::Matrix::translate(0.f,0.f,0.f);
//    osg::Matrix rotate= osg::Matrix::rotate(osg::DegreesToRadians(rx),osg::Vec3(1,0,0),osg::DegreesToRadians(ry),osg::Vec3(0,1,0),osg::DegreesToRadians(rz),osg::Vec3(0,0,1));
//    osg::Matrix scale = osg::Matrix::scale(sx,sy,sz);
//    osg::Matrix finalMatrix = siz*scale*rotate*trans;
    transform->setMatrix(trans);

    //Add shape to parent
    transform->addChild(geode);

    //Add transform to root
    mRoot->addChild(transform);
    create_box1();
    create_box2();
    create_box3();
    create_ground();
    create_outerWalls();

}
    void OSGWidget::create_box1()
{
    //Create the box
    osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 1.f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
    sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
    sd->setName( "Box" );

    //Create the node to hold the box
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    // Set material for basic lighting and enable depth tests. Else, the box
    // will suffer from rendering errors.
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    //Set up transform parent node.
    osg::MatrixTransform* transform= new osg::MatrixTransform;
    osg::Matrix scale = osg::Matrix::scale(20.0f,1.0f,1.0f);
    osg::Matrix trans = osg::Matrix::translate(10.f,0.f,0.f);
    transform->setMatrix(scale*trans);

    //Add shape to parent
    transform->addChild(geode);

    //Add transform to root
    mRoot->addChild(transform);
}
    void OSGWidget::create_box2()
{
    //Create the box
    osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 1.f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
    sd->setColor( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
    sd->setName( "Box" );

    //Create the node to hold the box
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    // Set material for basic lighting and enable depth tests. Else, the box
    // will suffer from rendering errors.
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    //Set up transform parent node.
    osg::MatrixTransform* transform= new osg::MatrixTransform;
    osg::Matrix scale = osg::Matrix::scale(1.0f,20.0f,1.0f);
    osg::Matrix trans = osg::Matrix::translate(0.f,10.f,0.f);
    transform->setMatrix(scale*trans);

    //Add shape to parent
    transform->addChild(geode);

    //Add transform to root
    mRoot->addChild(transform);
}
    void OSGWidget::create_box3()
    {
        //Create the box
        osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 1.f );
        osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
        sd->setColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
        sd->setName( "Box" );

        //Create the node to hold the box
        osg::Geode* geode = new osg::Geode;
        geode->addDrawable( sd );

        // Set material for basic lighting and enable depth tests. Else, the box
        // will suffer from rendering errors.
        osg::StateSet* stateSet = geode->getOrCreateStateSet();
        osg::Material* material = new osg::Material;

        material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
        stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
        stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

        //Set up transform parent node.
        osg::MatrixTransform* transform= new osg::MatrixTransform;
        osg::Matrix scale = osg::Matrix::scale(1.0f,1.0f,20.0f);
        osg::Matrix trans = osg::Matrix::translate(0.f,0.f,10.f);
        transform->setMatrix(scale*trans);

        //Add shape to parent
        transform->addChild(geode);

        //Add transform to root
        mRoot->addChild(transform);
    }
    void OSGWidget::create_ground()
{
    //Create the box
    osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 1.0f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
    sd->setColor( osg::Vec4( 0.9f, 0.9f, 0.9f, 1.f ) );
    sd->setName( "ground" );

    //Create the node to hold the box
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    // Set material for basic lighting and enable depth tests. Else, the box
    // will suffer from rendering errors.
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    //Set up transform parent node.
    osg::MatrixTransform* transform= new osg::MatrixTransform;
    osg::Matrix scale = osg::Matrix::scale(1000.0f,1000.0f,0.01f);
    osg::Matrix trans = osg::Matrix::translate(500.f,500.f,0.f);
    transform->setMatrix(scale*trans);

    //Add shape to parent
    transform->addChild(geode);

    //Add transform to root
    mRoot->addChild(transform);
    }

    void OSGWidget::create_outerWalls()
    {
        ///All naming schemes will go clockwise starting at the origin.
        std::vector<osg::Matrix> scales;
        scales.push_back(osg::Matrix::scale(10.f,1000.f,10.f));
        scales.push_back(osg::Matrix::scale(1000.f,10.f,10.f));
        scales.push_back(osg::Matrix::scale(10.f,1000.f,10.f));
        scales.push_back(osg::Matrix::scale(1000.f,10.f,10.f));
        std::vector<osg::Matrix> translations;
        translations.push_back(osg::Matrix::translate(0.f,500.f,5.f));
        translations.push_back(osg::Matrix::translate(500.f,1000.f,5.f));
        translations.push_back(osg::Matrix::translate(1000.f,500.f,5.f));
        translations.push_back(osg::Matrix::translate(500.f,0.f,5.f));
        std::vector<std::string> names;
        names.push_back("wall1");
        names.push_back("wall2");
        names.push_back("wall3");
        names.push_back("wall4");
        for(int i{0};i<4;i++)
        {
            //Create the box
            osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 1.0f );
            osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
            sd->setColor( osg::Vec4( 0.9f, 0.9f, 0.9f, 1.f ) );
            sd->setName( names[i]);

            //Create the node to hold the box
            osg::Geode* geode = new osg::Geode;
            geode->addDrawable( sd );

            // Set material for basic lighting and enable depth tests. Else, the box
            // will suffer from rendering errors.
            osg::StateSet* stateSet = geode->getOrCreateStateSet();
            osg::Material* material = new osg::Material;

            material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
            stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
            stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

            //Set up transform parent node.
            osg::MatrixTransform* transform= new osg::MatrixTransform;
            //osg::Matrix scale = osg::Matrix::scale(1000.0f,10.0f,10.f);
            //osg::Matrix rot = osg::Matrix::rotate(rotations(i));
           //osg::Matrix trans = osg::Matrix::translate(500.f,500.f,0.f);
            transform->setMatrix(scales[i]*translations[i]);

            //Add shape to parent
            transform->addChild(geode);

            //Add transform to root
            mRoot->addChild(transform);
        }
    }

    void OSGWidget::create_wall(double xCenter, double yCenter, double xWidth, double yHeight)
    {
        //Create the box
        osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, 0.f ), 1.f );
        osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
        sd->setColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
        sd->setName( "Wall" );

        //Create the node to hold the box
        osg::Geode* geode = new osg::Geode;
        geode->addDrawable( sd );

        // Set material for basic lighting and enable depth tests. Else, the box
        // will suffer from rendering errors.
        osg::StateSet* stateSet = geode->getOrCreateStateSet();
        osg::Material* material = new osg::Material;

        material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
        stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
        stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

        //Set up transform parent node.
        osg::MatrixTransform* transform= new osg::MatrixTransform;
        osg::Matrix scale = osg::Matrix::scale(xWidth,yHeight,10.0f);
        osg::Matrix trans = osg::Matrix::translate(xCenter,yCenter,5.f);
        transform->setMatrix(scale*trans);

        //Add shape to parent
        transform->addChild(geode);

        //Add transform to root
        mRoot->addChild(transform);
    }


//void OSGWidget::create_shape(Shape *s)
//{
////    QMessageBox *msgbox = new QMessageBox;
//    QString type = s->get_type();
//    if(type =="Box")
//    {
//        Box *b = dynamic_cast<Box*>(s);
//        create_box(b);
////        msgbox->setText(QString::number(mRoot->getNumChildren()));
//    }
//    else if (type =="Cone")
//    {
//        Cone *c = dynamic_cast<Cone*>(s);
//        create_cone(c);
////        msgbox->setText(QString::number(mRoot->getNumChildren()));
//    }
//    else if(type == "Ellipsoid")
//    {
//        Ellipsoid *e = dynamic_cast<Ellipsoid*>(s);
//        create_ellipsoid(e);
////        msgbox->setText(QString::number(mRoot->getNumChildren()));
//    }
////    msgbox->show();
//}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
    this->makeCurrent();

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    this->paintGL();

    painter.end();

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
    this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
    mGraphicsWindow->resized( this->x(), this->y(), width, height );

    this->on_resize( width, height );
}

void OSGWidget::keyPressEvent( QKeyEvent* event )
{
    QString keyString   = event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    if( event->key() == Qt::Key_H )
    {
        this->go_home();
        return;
    }

    this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::keyReleaseEvent( QKeyEvent* event )
{
    QString keyString   = event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    this->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::mouseMoveEvent( QMouseEvent* event )
{
    auto pixelRatio = this->devicePixelRatio();

    this->getEventQueue()->mouseMotion( static_cast<float>( event->x() * pixelRatio ),
                                        static_cast<float>( event->y() * pixelRatio ) );
}

void OSGWidget::mousePressEvent( QMouseEvent* event )
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch( event->button() )
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    auto pixelRatio = this->devicePixelRatio();

    this->getEventQueue()->mouseButtonPress( static_cast<float>( event->x() * pixelRatio ),
                                             static_cast<float>( event->y() * pixelRatio ),
                                             button );

}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch( event->button() )
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    auto pixelRatio = this->devicePixelRatio();

    this->getEventQueue()->mouseButtonRelease( static_cast<float>( pixelRatio * event->x() ),
                                               static_cast<float>( pixelRatio * event->y() ),
                                               button );
}

void OSGWidget::wheelEvent( QWheelEvent* event )
{
    event->accept();
    int delta = event->delta();

    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                                 : osgGA::GUIEventAdapter::SCROLL_DOWN;

    this->getEventQueue()->mouseScroll( motion );
}

bool OSGWidget::event( QEvent* event )
{
    bool handled = QOpenGLWidget::event( event );

    // This ensures that the OSG widget is always going to be
    // repainted after the user performed some interaction. 
    // Doing this in the event handler ensures
    // that we don't forget about some event and prevents duplicate code.
    switch( event->type() )
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::Wheel:
        this->update();
        break;

    default:
        break;
    }

    return handled;
}

void OSGWidget::create_triangle()
{

    //Define the geometry of the triangle
   osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
   vertices->push_back(osg::Vec3(0,0,0));
   vertices->push_back(osg::Vec3(1,0,0));
   vertices->push_back(osg::Vec3(.5,1,0));

   osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
   normals->push_back(osg::Vec3(0,0,1));
   normals->push_back(osg::Vec3(0,0,1));
   normals->push_back(osg::Vec3(0,0,1));

   osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt( GL_TRIANGLES );
   indices->push_back(0);
   indices->push_back(1);
   indices->push_back(2);


   //Define the triangle color
   osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
   colors->push_back( osg::Vec4(1, 0, 1, 1) );


   //Create the osg geometry for the triangle
   osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
   geom->setVertexArray( vertices.get() );
   geom->setNormalArray( normals.get() );
   geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
   geom->setColorArray( colors.get() );
   geom->setColorBinding( osg::Geometry::BIND_OVERALL );
   geom->addPrimitiveSet( new osg::DrawArrays(GL_TRIANGLES, 0, 3) );
   geom->addPrimitiveSet( indices.get() );


   //Set material for basic lighting and enable depth tests.
   osg::StateSet* stateSet = geom->getOrCreateStateSet();
   osg::Material* material = new osg::Material;

   material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
   stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
   stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


   //Create the node to hold the triangle
   osg::ref_ptr<osg::Geode> geode = new osg::Geode;
   geode->addDrawable( geom.get() );

   //Create the parent transform node
   osg::MatrixTransform* transform = new osg::MatrixTransform;
   osg::Matrix matrix = osg::Matrix::rotate(osg::DegreesToRadians((float)90),1,0,0);
   transform->setMatrix(matrix);

   //Add the triangle node to the parent
   transform->addChild(geode);

   //Add the transform to the root
   mRoot->addChild(transform);
}

void OSGWidget::clear()
{
    mRoot->removeChildren(0, mRoot->getNumChildren());

    create_box1();
    create_box2();
    create_box3();
    create_ground();
    //create_outerWalls();
}

//void OSGWidget::create_ellipsoid(Ellipsoid *e)
void OSGWidget::create_player(double xCenter,double yCenter,double radius)
{
    double radx{1},rady{1},radz{1};
    double tx{xCenter},ty{yCenter},tz{radius};
    double r{0},g{1},b{0};
    double rx{0},ry{0},rz{0};
    double sx{radius},sy{radius},sz{radius};
/*    e->get_scale(sx,sy,sz);
    e->get_rotation(rx,ry,rz);
    e->get_color(r,g,b);
    e->get_size(radx,rady,radz);
    e->get_translation(tx,ty,tz);*/
    //osg::Sphere *sphere = new osg::Sphere(osg::Vec3(0.f,0.f,1.f),0.5f);
    osg::Sphere *sphere = new osg::Sphere(osg::Vec3(0,0,0),1.0f);
    osg::ShapeDrawable *sd = new osg::ShapeDrawable(sphere);

    //sd->setColor(osg::Vec4(1.0f,0.f,0.f,1.f));
    sd->setColor(osg::Vec4(r,g,b,1.f));
    sd->setName("SpherePlayer");

    osg::Geode *geode = new osg::Geode;
    geode->addDrawable(sd);

    // Set material for basic lighting and enable depth tests. Else, the box
    // will suffer from rendering errors.
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


    //Set up transform parent node.
//    osg::MatrixTransform* transform= new osg::MatrixTransform;
//    transform->setMatrix(osg::Matrix::translate(cx,cy,cz));
    osg::MatrixTransform* transform = new osg::MatrixTransform;
 //   osg::Matrix matrix = osg::Matrix::rotate(osg::DegreesToRadians((float)90),1,0,0);
    osg::Matrix siz = osg::Matrix::scale(radx,rady,radz);
    osg::Matrix trans = osg::Matrix::translate(tx,ty,tz);
    osg::Matrix rotate= osg::Matrix::rotate(osg::DegreesToRadians(rx),osg::Vec3(1,0,0),osg::DegreesToRadians(ry),osg::Vec3(0,1,0),osg::DegreesToRadians(rz),osg::Vec3(0,0,1));
    osg::Matrix scale = osg::Matrix::scale(sx,sy,sz);
    osg::Matrix finalMatrix = siz*scale*rotate*trans;
    transform->setMatrix(finalMatrix);

    //Add shape to parent
    transform->addChild(geode);

    //Add transform to root
    mRoot->addChild(transform);
}

//void OSGWidget::create_cone(Cone *c)//double h,double radx,double rady)
//{
//    double h{0},radx{0},rady{0};
//    double tx{0},ty{0},tz{0};
//    double r{0},g{0},b{0};
//    double rx{0},ry{0},rz{0};
//    double sx{0},sy{0},sz{0};
//    c->get_scale(sx,sy,sz);
//    c->get_rotation(rx,ry,rz);
//    c->get_color(r,g,b);
//    c->get_translation(tx,ty,tz);
//    osg::Cone *cone = new osg::Cone(osg::Vec3(1.f,1.f,1.f),0.5f,2.0f);
//    //osg::Cone *cone = new osg::Cone(osg::Vec3(0,0,0),radx,h);
//    osg::ShapeDrawable *sd = new osg::ShapeDrawable(cone);
//    //sd->setColor(osg::Vec4(1.0f,0.f,0.f,1.f));
//    sd->setColor(osg::Vec4(r,g,b,1.f));
//    sd->setName("Cone1");

//    osg::Geode *geode = new osg::Geode;
//    geode->addDrawable(sd);

//    // Set material for basic lighting and enable depth tests. Else, the box
//    // will suffer from rendering errors.
//    osg::StateSet* stateSet = geode->getOrCreateStateSet();
//    osg::Material* material = new osg::Material;

//    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

//    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
//    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


//    //Set up transform parent node.
////    osg::MatrixTransform* transform= new osg::MatrixTransform;
////    transform->setMatrix(osg::Matrix::translate(tx,ty,tz));
//    //Create the parent transform node
//    osg::MatrixTransform* transform = new osg::MatrixTransform;
// //   osg::Matrix matrix = osg::Matrix::rotate(osg::DegreesToRadians((float)90),1,0,0);
//    osg::Matrix trans = osg::Matrix::translate(tx,ty,tz);
//    osg::Matrix rotate= osg::Matrix::rotate(osg::DegreesToRadians(rx),osg::Vec3(1,0,0),osg::DegreesToRadians(ry),osg::Vec3(0,1,0),osg::DegreesToRadians(rz),osg::Vec3(0,0,1));
//    osg::Matrix scale = osg::Matrix::scale(sx,sy,sz);
//    osg::Matrix finalMatrix = scale*rotate*trans;
//    transform->setMatrix(finalMatrix);
//    //Add shape to parent
//    transform->addChild(geode);

//    //Add transform to root
//    mRoot->addChild(transform);
//}

void OSGWidget::remove_shape(int index)
{
    mRoot->removeChild(index);
}


////void OSGWidget::create_box()
//void OSGWidget::create_box(Box *box)//double h,double w,double d)
//{
//    double h{0},w{0},d{0};
//    double r{0},g{0},b{0};
//    double tx{0},ty{0},tz{0};
//    double rx{0},ry{0},rz{0};
//    double sx{0},sy{0},sz{0};
//    box->get_scale(sx,sy,sz);
//    box->get_rotation(rx,ry,rz);
//    box->get_color(r,g,b);
//    box->get_size(h,w,d);
//    box->get_translation(tx,ty,tz);
////

//    //Define the geometry of the box
//   osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
//   //Top plane triangle1
//   vertices->push_back(osg::Vec3(-w/2,d/2,h/2));
//   vertices->push_back(osg::Vec3(w/2,d/2,h/2));
//   vertices->push_back(osg::Vec3(w/2,-d/2,h/2));
//   //top plane triangle2
//   vertices->push_back(osg::Vec3(w/2,-d/2,h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,h/2));
//   vertices->push_back(osg::Vec3(-w/2,d/2,h/2));
//   //Bottom plane triangle1
//   vertices->push_back(osg::Vec3(w/2,-d/2,-h/2));
//   vertices->push_back(osg::Vec3(w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,d/2,-h/2));
//   //Bottom plane triangle2
//   vertices->push_back(osg::Vec3(-w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,-h/2));
//   vertices->push_back(osg::Vec3(w/2,-d/2,-h/2));

//   //side plane left triangle 1
//   vertices->push_back(osg::Vec3(-w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,d/2,h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,h/2));
//   //side plane left triangle 2
//   vertices->push_back(osg::Vec3(-w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,h/2));

//   //side plane Right triangle 1
//   vertices->push_back(osg::Vec3(w/2,-d/2,h/2));
//   vertices->push_back(osg::Vec3(w/2,d/2,h/2));
//   vertices->push_back(osg::Vec3(w/2,d/2,-h/2));
//   //side plane Right triangle 2
//   vertices->push_back(osg::Vec3(w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(w/2,-d/2,-h/2));
//   vertices->push_back(osg::Vec3(w/2,-d/2,h/2));

//   //front plane triangle 1
//   vertices->push_back(osg::Vec3(w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(w/2,d/2,h/2));
//   vertices->push_back(osg::Vec3(-w/2,d/2,h/2));
//   //front plane triangle 2
//   vertices->push_back(osg::Vec3(-w/2,d/2,h/2));
//   vertices->push_back(osg::Vec3(-w/2,d/2,-h/2));
//   vertices->push_back(osg::Vec3(w/2,d/2,-h/2));

//   //Back plane triangle 1
//   vertices->push_back(osg::Vec3(-w/2,-d/2,h/2));
//   vertices->push_back(osg::Vec3(w/2,-d/2,h/2));
//   vertices->push_back(osg::Vec3(w/2,-d/2,-h/2));
//   //Back plane triangle 2
//   vertices->push_back(osg::Vec3(w/2,-d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,-h/2));
//   vertices->push_back(osg::Vec3(-w/2,-d/2,h/2));

//   osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//   for(int i{0};i<6;i++)
//   {
//      normals->push_back(osg::Vec3(0,0,1));
//   }

////   normals->push_back(osg::Vec3(0,0,1));
////   normals->push_back(osg::Vec3(0,0,1));

////   normals->push_back(osg::Vec3(0,0,1));
////   normals->push_back(osg::Vec3(0,0,1));
////   normals->push_back(osg::Vec3(0,0,1));

//   for(int i{0};i<6;i++)
//   {
//       normals->push_back(osg::Vec3(0,0,-1));
//   }
////   normals->push_back(osg::Vec3(0,0,-1));
////   normals->push_back(osg::Vec3(0,0,-1));

////   normals->push_back(osg::Vec3(0,0,-1));
////   normals->push_back(osg::Vec3(0,0,-1));
////   normals->push_back(osg::Vec3(0,0,-1));

//   for(int i{0};i<6;i++)
//   {
//       normals->push_back(osg::Vec3(0,-1,0));
//   }
////   normals->push_back(osg::Vec3(0,-1,0));
////   normals->push_back(osg::Vec3(0,-1,0));

////   normals->push_back(osg::Vec3(0,-1,0));
////   normals->push_back(osg::Vec3(0,-1,0));
////   normals->push_back(osg::Vec3(0,-1,0));

//   for(int i{0};i<6;i++)
//   {
//       normals->push_back(osg::Vec3(0,1,0));
//   }
////   normals->push_back(osg::Vec3(0,1,0));
////   normals->push_back(osg::Vec3(0,1,0));

////   normals->push_back(osg::Vec3(0,1,0));
////   normals->push_back(osg::Vec3(0,1,0));
////   normals->push_back(osg::Vec3(0,1,0));


//   for(int i{0};i<6;i++)
//   {
//       normals->push_back(osg::Vec3(-1,0,0));
//   }
////   normals->push_back(osg::Vec3(-1,0,0));
////   normals->push_back(osg::Vec3(-1,0,0));

////   normals->push_back(osg::Vec3(-1,0,0));
////   normals->push_back(osg::Vec3(-1,0,0));
////   normals->push_back(osg::Vec3(-1,0,0));

//   for(int i{0};i<6;i++)
//   {
//       normals->push_back(osg::Vec3(1,0,0));
//   }
////   normals->push_back(osg::Vec3(1,0,0));
////   normals->push_back(osg::Vec3(1,0,0));

////   normals->push_back(osg::Vec3(1,0,0));
////   normals->push_back(osg::Vec3(1,0,0));
////   normals->push_back(osg::Vec3(1,0,0));

//   osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt( GL_TRIANGLES );
//   for (int i{0}; i<36; i++)
//       indices->push_back(i);

//   //Define the triangle color
//   osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
//   colors->push_back( osg::Vec4(r, g, b, 1) );




//   //Create the osg geometry for the triangle
//   osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
//   geom->setVertexArray( vertices.get() );
//   geom->setNormalArray( normals.get() );
//   geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
//   geom->setColorArray( colors.get() );
//   geom->setColorBinding( osg::Geometry::BIND_OVERALL );
//   geom->addPrimitiveSet( new osg::DrawArrays(GL_TRIANGLES, 0, 3) );
//   geom->addPrimitiveSet( indices.get() );



//   //Set material for basic lighting and enable depth tests.
//   osg::StateSet* stateSet = geom->getOrCreateStateSet();
//   osg::Material* material = new osg::Material;

//   material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
//   stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
//   stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );


//   //Create the node to hold the triangle
//   osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//   geode->addDrawable( geom.get() );


//   //Create the parent transform node
//   osg::MatrixTransform* transform = new osg::MatrixTransform;
////   osg::Matrix matrix = osg::Matrix::rotate(osg::DegreesToRadians((float)90),1,0,0);
//   osg::Matrix trans = osg::Matrix::translate(tx,ty,tz);
//   osg::Matrix rotate= osg::Matrix::rotate(osg::DegreesToRadians(rx),osg::Vec3(1,0,0),osg::DegreesToRadians(ry),osg::Vec3(0,1,0),osg::DegreesToRadians(rz),osg::Vec3(0,0,1));
//   osg::Matrix scale = osg::Matrix::scale(sx,sy,sz);
//   osg::Matrix finalMatrix = scale*rotate*trans;
//   transform->setMatrix(finalMatrix);

////   osg::MatrixTransform *translate = new osg::MatrixTransform;
////   osg::Matrix mat = osg::Matrix::translate(tx,ty,tz);
////   translate->setMatrix(mat);

//   //Add the triangle node to the parent
//   transform->addChild(geode);

//   //Add the transform to the root
//   mRoot->addChild(transform);

//}



void OSGWidget::go_home()
{
    osgViewer::ViewerBase::Views views;
    mViewer->getViews( views );

    for(osgViewer::View* view:views)
    {
        view->home();
    }
}

void OSGWidget::on_resize( int width, int height )
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras( cameras );

    auto pixelRatio = this->devicePixelRatio();

    cameras[0]->setViewport( 0, 0, width * pixelRatio, height * pixelRatio );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}


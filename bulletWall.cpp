//-------------------------------------------------------
// Filename: bulletWall.cpp
//
// Description:  The cpp file for the qt5 bullet bouncy ball example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/7/17
//
// Owner: Corey McBride
// Editor: Jacob Tovar
//-------------------------------------------------------
#include "bulletWall.h"
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

class WallUpdateCallback: public osg::NodeCallback
{
private:
    btRigidBody *_body;

public:
    WallUpdateCallback(btRigidBody *body) :
        _body(body)
    {
    }

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        btScalar m[16];

        _body->getCenterOfMassTransform().getOpenGLMatrix(m);
        //btDefaultMotionState* myMotionState = (btDefaultMotionState*) _body->getMotionState();
        //myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);

        osg::Matrixf mat(m);

        osg::MatrixTransform *pat = dynamic_cast<osg::MatrixTransform *> (node);
        pat->setMatrix(mat);

        traverse(node, nv);
    }
};

bulletWall::bulletWall()
{
  create();
}
bulletWall::bulletWall(int size, QVector4D& color)
{
    mSize=size;
    mColor=color;

    create();
}

bulletWall::bulletWall(double xCenter, double yCenter, double xWidth, double yHeight,QVector4D& color)
{
    mxCenter = &xCenter;
    myCenter = &yCenter;
    mxWidth = xWidth;
    myHeight = yHeight;
    mColor = color;
    create();
}
bulletWall::bulletWall(osg::Vec3 pos, int size, QVector4D& color)
{
    //mSize=size;
    mColor=color;
    mPos = pos;
    create();
}

void bulletWall::getWallDim(double *xCenter, double *yCenter)
{
    xCenter = mxCenter;
    yCenter = myCenter;
}

void bulletWall::create()
{
    mbulletWallShape = new btBoxShape(btVector3(mxWidth/1.75,myHeight/1.75,30*0.5));
    mbulletWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(*mxCenter,*myCenter,20*.5)));

    mRigidCI= new btRigidBody::btRigidBodyConstructionInfo(0,mbulletWallMotionState,mbulletWallShape,btVector3(0,0,0));
    mRigidCI->m_restitution = 0.8; //This can change to make the maze/level more difficult.
    mRigidBody = new btRigidBody(*mRigidCI);
    create_mesh();
}
void bulletWall::create_mesh()
{
    mOSGBox  = new osg::Box( osg::Vec3(0,0,10) , mxWidth,myHeight,20 );//osg::Vec3( 0.f, 0.f, 0.f )

    osg::ShapeDrawable* sd = new osg::ShapeDrawable( mOSGBox );
    //sd->setColor(osg::Vec4(0.2,0.2,0.2));
    sd->setColor(  osg::Vec4(mColor[0], mColor[1], mColor[2],mColor[3]));
    sd->setName( "bulletWall" );
    //This is used so that a second player can go through the list of maze walls.
    mWallShape = sd;
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    // Set material for basic lighting and enable depth tests. Else, the sphere
    // will suffer from rendering errors.
    {
        osg::StateSet* stateSet = geode->getOrCreateStateSet();
        osg::Material* material = new osg::Material;

        material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

        stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
        stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    }
    mTransform = new osg::MatrixTransform;
    mTransform->setUpdateCallback(new WallUpdateCallback(mRigidBody));
    mTransform->addChild(geode);


}

void bulletWall::destroy()
{
    delete mRigidBody;
    delete mRigidCI;
    delete mbulletWallShape;
    delete mbulletWallMotionState;
}



void bulletWall::changeWallColor(osg::Vec4 color)
{
    mWallShape->setColor(color);
}

//Move OSG and Bullet wall to new location
void bulletWall::translateWall(bool up)
{
    btScalar pre[16];
    mRigidBody->getCenterOfMassTransform().getOpenGLMatrix(pre);

    bool valid{false};

    //Check if wall is horizontal or vertical
    if(mxWidth==10.f)
    {
        //Vertical Wall
        if (up)
        {
            mRigidBody->translate(btVector3(0,myHeight,0));
            //trans = {osg::Matrix::translate(0,myHeight,0)};
//            *myCenter = *myCenter + myHeight;
        }
        else
        {
            mRigidBody->translate(btVector3(0,-myHeight,0));
//            trans = {osg::Matrix::translate(0,-myHeight,0)};
//            *myCenter = *myCenter-myHeight;
        }
        valid = true;
    }
    else if(myHeight==10.f)
    {
        //horizontal wall
        if(up)
        {
            mRigidBody->translate(btVector3(mxWidth,0,0));
//            *mxCenter = *mxCenter + mxWidth;
        }
        else
        {
            mRigidBody->translate(btVector3(-mxWidth,0,0));
//            trans={osg::Matrix::translate(mxWidth,0,0)};
//            *mxCenter = *mxCenter - mxWidth;
        }

        valid = true;
    }

    btScalar post[16];
    mRigidBody->getCenterOfMassTransform().getOpenGLMatrix(post);

}


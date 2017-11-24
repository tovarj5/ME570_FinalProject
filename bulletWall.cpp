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
//-------------------------------------------------------
#include "bulletWall.h"
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

bulletWall::bulletWall()
{
  //mSize=1000;
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
    mxCenter = xCenter;
    myCenter = yCenter;
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

void bulletWall::create()
{
    mbulletWallShape = new btBoxShape(btVector3(mxWidth,myHeight,20*0.5));
    mbulletWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(mxCenter,myCenter,20*.5)));

    mRigidCI= new btRigidBody::btRigidBodyConstructionInfo(0,mbulletWallMotionState,mbulletWallShape,btVector3(0,0,0));
    mRigidCI->m_restitution = 0.8; //This can change to make the maze/level more difficult.
    mRigidBody = new btRigidBody(*mRigidCI);
    create_mesh();
}
void bulletWall::create_mesh()
{
    mOSGBox  = new osg::Box( osg::Vec3(mxCenter,myCenter,10) , mxWidth,myHeight,20 );//osg::Vec3( 0.f, 0.f, 0.f )
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( mOSGBox );
    //sd->setColor(osg::Vec4(0.2,0.2,0.2));
    sd->setColor(  osg::Vec4(mColor[0], mColor[1], mColor[2],mColor[3]));
    sd->setName( "bulletWall" );

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

    mTransform->addChild(geode);

}

void bulletWall::destroy()
{
    delete mRigidBody;
    delete mRigidCI;
    delete mbulletWallShape;
    delete mbulletWallMotionState;
}

void bulletWall::draw(QMatrix4x4 &V_matrix, QMatrix4x4 &P_matrix)
{
    // This part of the code updates the rigid body
    // position in the bullet world. It also gets that
    // position as an OpenGL format.
    mRigidBody->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(btMat);

    M=QMatrix4x4(btMat);
    M=M.transposed();
    M.translate(mxCenter,myCenter,10);



}


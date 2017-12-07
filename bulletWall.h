//-------------------------------------------------------
// Filename: bulletWall.h
//
// Description:  The h file for the qt5 bullet bouncy ball example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/7/17
//
// Owner: Corey McBride
//-------------------------------------------------------

#ifndef BULLETWALL_H
#define BULLETWALL_H
#include <QMatrix4x4>
#include "btBulletDynamicsCommon.h"
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

class bulletWall
{
public:
    bulletWall();
    bulletWall(int size,QVector4D& color);
    bulletWall(double xCenter, double yCenter, double xWidth, double yHeight, QVector4D &color);
    btRigidBody* getRigidBodyPtr() {return mRigidBody;}
    osg::Node* getNode() {return mTransform.get();}

    void changeWallColor(osg::Vec4 color);
    void translateWall(bool up);
    bulletWall(osg::Vec3 pos, int size, QVector4D &color);
    void getWallDim(double *xCenter, double *yCenter);

private:
    double mSize;
    double *mxCenter{0},*myCenter{0};
    double mxWidth{0},myHeight{0},mzHeight{0};
    osg::Vec3 mPos;
    btCollisionShape* mbulletWallShape;
    btDefaultMotionState* mbulletWallMotionState;
    btRigidBody* mRigidBody;
    btRigidBody::btRigidBodyConstructionInfo* mRigidCI;
    btScalar btMat[16];
    QMatrix4x4  M;
    btTransform trans;
    QVector4D mColor;
    osg::ShapeDrawable *mWallShape;


    void create();
    void destroy();
    void create_mesh();

    osg::ref_ptr<osg::MatrixTransform> mTransform;
    osg::ref_ptr<osg::Box> mOSGBox;

};

#endif // bulletWall_H

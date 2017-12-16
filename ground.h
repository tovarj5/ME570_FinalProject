//-------------------------------------------------------
// Filename: Ground.h
//
// Description:  The h file for the qt5 bullet bouncy ball example.
// And has been modified to be dymanic in creating the maze ground.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/7/17
//
// Owner: Corey McBride
// Editor : Jacob Tovar
//-------------------------------------------------------

#ifndef GROUND_H
#define GROUND_H
#include <QMatrix4x4>
#include "btBulletDynamicsCommon.h"
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

class Ground
{
public:
    Ground();
    Ground(int size,QVector4D& color);
    Ground(double xCenter,double yCenter,double xWidth,double yHeight);
    btRigidBody* getRigidBodyPtr() {return mRigidBody;}
    osg::Node* getNode() {return mTransform.release();}

    void draw(QMatrix4x4 &V_matrix, QMatrix4x4 &P_matrix);


    Ground(osg::Vec3 pos, int size, QVector4D &color);
private:
    double mSize;
    osg::Vec3 mPos;
    btCollisionShape* mGroundShape;
    btDefaultMotionState* mGroundMotionState;
    btRigidBody* mRigidBody;
    btRigidBody::btRigidBodyConstructionInfo* mRigidCI;
    btScalar btMat[16];
    QMatrix4x4  M;
    btTransform trans;
    QVector4D mColor;


    void create();
    void destroy();
    void create_mesh();

    osg::ref_ptr<osg::MatrixTransform> mTransform;
    osg::ref_ptr<osg::Box> mOSGBox;

};

#endif // GROUND_H

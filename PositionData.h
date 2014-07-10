#ifndef POSITIONDATA_H_INCLUDED
#define POSITIONDATA_H_INCLUDED

#include <GLTools.h>
#include <math3d.h>

struct PositionData{
GLdouble x;
GLdouble y;
GLdouble alfa;

    PositionData();

    PositionData(GLdouble _x,GLdouble _y,GLdouble _alfa);
    void getTransformationMatrix(M3DMatrix44f& res);
};

#endif // POSITIONDATA_H_INCLUDED

#ifndef POSITIONDATA_H_INCLUDED
#define POSITIONDATA_H_INCLUDED

#include <GLTools.h>

struct PositionData{
GLint x;
GLint y;
GLdouble alfa;

    PositionData();

    PositionData(GLint _x,GLint _y,GLdouble _alfa);
};

#endif // POSITIONDATA_H_INCLUDED

#ifndef TRACK_H_INCLUDED
#define TRACK_H_INCLUDED

#include <vector>
#include <GLTriangleBatch.h>
#include "Coordinate.h"
#include "PositionData.h"
class Track{

private:
    std::vector<Coordinate> controlPoints;

    Coordinate   derivalt(GLdouble t,GLdouble R);

    Coordinate bezier(GLdouble t);

public:
    void addControlPoint(Coordinate xy);

    int getControlPointIndexAt(Coordinate xy,GLdouble r);

    void setControlPointAtIndex(int index,Coordinate xy);

    GLTriangleBatch* getBatch();

    PositionData getCarPosition(GLdouble t,GLdouble r );

    void finalPoint();

    GLBatch* getControlPointBatch();

    void setAfterFinalControlPointAtIndex(int index,Coordinate xy);


};
#endif

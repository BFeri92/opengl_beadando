#ifndef TRACKd_H_INCLUDED
#define TRACKd_H_INCLUDED

#include <vector>
#include <GLTriangleBatch.h>
#include <math3d.h>
#include <iostream>
#include "Coordinate.h"
#include "PositionData.h"

class Track{

private:
    std::vector<Coordinate> controlPoints;

public:
    void addControlPoint(Coordinate xy)
    {
		controlPoints.push_back(xy);
	}

    int getControlPointIndexAt(Coordinate xy,GLdouble r)
    {
		return 1;
	}

    void setControlPointAtIndex(int index,Coordinate xy)
    {
		if (index!=1) std::cout<<"setControlPoint rossz indexet kap!"<<std::endl;
	}

    GLTriangleBatch* getBatch()
    {
		/*
		double prevX = cos(0);
		double prevY = sin(0);
		M3DVector3f verts[3]= {{0,0,0},{0,0,0},{0,0,0}};
		M3DVector3f vNorms[3]={{0,1,0},{0,1,0},{0,1,0}};
		M3DVector2f vTexCoords[3]={{0,0},{0,1},{1,1}};
		double curveX;
		double curveY;
		GLTriangleBatch* res = new GLTriangleBatch();
		for (int i=.01; i<2.0*3.14159265359; i+=.01)
		{
			curveX=cos(i);
			curveY=sin(i);
			verts[0][0]=prevX*0.7;
			verts[0][1]=prevY*0.7;
			res.addTriangle
			prevX=curveX;
			prevY=curveY;
		}
		return res;*/
/*
		M3DVector3f verts[3]={{0,0,0},{0,10,0},{10,10,0}};
		M3DVector3f norms[3];
		m3dFindNormal(norms[0], verts[0], verts[1], verts[2]);
		norms[2][0]=norms[1][0]=norms[0][0];
		norms[2][1]=norms[1][1]=norms[0][1];
		norms[2][2]=norms[1][2]=norms[0][2];
		
		M3DVector2f vTexCoords[3]={{0,0},{0,1},{1,1}};
		GLTriangleBatch* res = new GLTriangleBatch();
		res->BeginMesh(3);
		res->AddTriangle(verts, norms, vTexCoords);*/
		
		GLTriangleBatch* res = new GLTriangleBatch();
		gltMakeSphere(*res, 1.0f, 52, 26);
		
		return res;
	}

    PositionData getCarPosition(GLdouble t,GLdouble r )
    {
	
	}

    void finalPoint()
    {
		
	}





};	
#endif

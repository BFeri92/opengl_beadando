#include "Track.h"
#include "Coordinate.h"
#include "PositionData.h"
#include <math.h>
#include <iostream>
#define PI 3.1415926535

void Track::addControlPoint(Coordinate xy){

    controlPoints.push_back( Coordinate(xy));

}

double dist( Coordinate P1,Coordinate P2){
            GLdouble t1 = P1.x - P2.x;
            GLdouble t2 = P1.y - P2.y;

        return t1 * t1 + t2 * t2;
}


int Track::getControlPointIndexAt(Coordinate xy, GLdouble r){
        int distance=r*r;

            for(int i=0;i<controlPoints.size();i++){
                if( dist(xy,controlPoints[i]) < distance)
                    return i;
            }
    return -1;
}


void Track::setControlPointAtIndex(int index,Coordinate xy){

        controlPoints[index]=xy;
}

void Track::setAfterFinalControlPointAtIndex(int index,Coordinate xy){

    Coordinate P=controlPoints[index];
    Coordinate displacement;

    displacement.x= P.x - xy.x ;
    displacement.y= P.x - xy.y ;


    if(index!=0 || index!=1 || index!=(controlPoints.size()-1) || index!=(controlPoints.size()-2) )
        controlPoints[index]=xy;
    else{

        if( index == 0 || index == (controlPoints.size()-1) ){
            controlPoints[0]=xy;
            controlPoints[(controlPoints.size()-1)]=xy;

            controlPoints[1].x+=displacement.x;
            controlPoints[1].y+=displacement.y;

            controlPoints[(controlPoints.size()-2)].x+=displacement.x;
            controlPoints[(controlPoints.size()-2)].y+=displacement.y;
        }
        if( index==1 ){
            controlPoints[1]=xy;

            controlPoints[0].x+=displacement.x;
            controlPoints[0].y+=displacement.y;

            controlPoints[(controlPoints.size()-1)].x+=displacement.x;
            controlPoints[(controlPoints.size()-1)].y+=displacement.y;

            controlPoints[(controlPoints.size()-2)].x+=displacement.x;
            controlPoints[(controlPoints.size()-2)].y+=displacement.y;

        }

        if( index==(controlPoints.size()-2)){
            controlPoints[(controlPoints.size()-2)]=xy;

            controlPoints[0].x+=displacement.x;
            controlPoints[0].y+=displacement.y;

            controlPoints[(controlPoints.size()-1)].x+=displacement.x;
            controlPoints[(controlPoints.size()-1)].y+=displacement.y;

            controlPoints[1].x+=displacement.x;
            controlPoints[1].y+=displacement.y;

        }


    }

}
//----------------------------------------------
GLdouble fakt(GLdouble n)
{
    return (n<=1 ? 1 :  n * fakt(n-1));
}

GLdouble B(GLdouble t,GLdouble i, GLdouble n)
{
    GLdouble Bi=0;
    Bi=( fakt(n)/(fakt(i)*fakt(n-i)) )*pow(t,i)*pow(1-t,n-i);

    return Bi;
}

GLdouble DerB(GLdouble u,GLdouble i, GLdouble n)
{
    GLdouble Der=0;
    if(u==0)
        u=0.0001;
    if(u==1)
        u=0.9999;

    Der=-1* (fakt(n)/(fakt(i)*fakt(n-i))) * pow(u,i-1) * pow(1-u,n-i-1) * (n*u-i);

    return Der;
}

Coordinate   Track::derivalt(GLdouble t,GLdouble R){
Coordinate P;
GLdouble    px=0;
GLdouble    py=0;
GLdouble    derx=0;
GLdouble    dery=0;

    for(GLint i=0;i<controlPoints.size();i++){
        derx+=controlPoints[i].x * DerB(t,i,controlPoints.size()-1);
        dery+=controlPoints[i].y * DerB(t,i,controlPoints.size()-1);
    }

        P.x=(derx/(sqrt(pow(derx,2)+pow(dery,2))) * R);
        P.y=(dery/(sqrt(pow(derx,2)+pow(dery,2))) * R);

return P;
}



Coordinate Track::bezier(GLdouble t){
Coordinate P;
    P.x=0;
    P.y=0;
    for(GLint i=0;i<controlPoints.size();i++){
        P.x+=controlPoints[i].x * B(t,i,controlPoints.size()-1);
        P.y+=controlPoints[i].y * B(t,i,controlPoints.size()-1);
    }


return P;
}
//------------------------------------------------

GLTriangleBatch* Track::getBatch(){
    GLTriangleBatch* _track = new GLTriangleBatch();

    double number=1.0 / 0.01;
    int trackWidth=20;

    Coordinate P1,P2, Pd1,Pd2;
    Coordinate P11,P22, Pd11,Pd22;

    _track->BeginMesh(2*3*number);

        M3DVector3f vVertex[3];
		M3DVector3f vNormal[3];
		M3DVector2f vTexture[3];

        GLdouble step=0.01;

		for(GLdouble t=0;t<1;t+=step){
            Pd1=derivalt(t,trackWidth);
            P1=bezier(t);
            P1.x+=-1.0*Pd1.y;
            P1.y+=Pd1.x;

            Pd2=derivalt(t,-1*trackWidth);
            P2=bezier(t);
            P2.x+=-1.0*Pd2.y;
            P2.y+=Pd2.x;

            Pd11=derivalt(t+step,trackWidth);
            P11=bezier(t+step);
            P11.x+=-1.0*Pd11.y;
            P11.y+=Pd11.x;

            Pd22=derivalt(t+step,-1*trackWidth);
            P22=bezier(t+step);
            P22.x+=-1.0*Pd22.y;
            P22.y+=Pd22.x;

            vVertex[0][0]=P1.x;
            vVertex[0][1]=0;
            vVertex[0][2]=P1.y;

            vVertex[1][0]=P2.x;
            vVertex[1][1]=0;
            vVertex[1][2]=P2.y;

            vVertex[2][0]=P22.x;
            vVertex[2][1]=0;
            vVertex[2][2]=P22.y;

            vNormal[0][0]=0.0f;
            vNormal[0][1]=0.0f;
            vNormal[0][2]=1.0f;

            vNormal[1][0]=0.0;
            vNormal[1][1]=0.0f;
            vNormal[1][2]=1.0f;

            vNormal[2][0]=0.0f;
            vNormal[2][1]=0.0f;
            vNormal[2][2]=1.0f;

            vTexture[0][0]=0.0f;
            vTexture[0][1]=0.0f;

            vTexture[1][0]=0.0f;
            vTexture[1][1]=1.0f;

            vTexture[2][0]=1.0f;
            vTexture[2][1]=1.0f;

            _track->AddTriangle(vVertex,vNormal,vTexture)  ;

            vVertex[0][0]=P1.x;
            vVertex[0][1]=0;
            vVertex[0][2]=P1.y;

            vVertex[1][0]=P11.x;
            vVertex[1][1]=0;
            vVertex[1][2]=P11.y;

            vVertex[2][0]=P22.x;
            vVertex[2][1]=0;
            vVertex[2][2]=P22.y;

             _track->AddTriangle(vVertex,vNormal,vTexture)  ;


		}

    _track->End();

 return _track;
}
GLBatch* Track::getControlPointBatch(){

    GLBatch* pointBatch = new GLBatch();

    pointBatch->Begin(GL_POINTS,controlPoints.size(),1);

        for(GLint i=0;i<controlPoints.size();i++){
            pointBatch->Normal3f(0.0f, 1.0f, 0.0f);
            pointBatch->MultiTexCoord2f(0, 1.0f, 1.0f);
            pointBatch->Vertex3f(controlPoints[i].x, 0, controlPoints[i].y);
        }
    pointBatch->End();

return pointBatch;
}
PositionData Track::getCarPosition(GLdouble t,GLdouble r ){
    PositionData pData;
    pData.x=0;
    pData.y=0;
    pData.alfa=0;
    Coordinate way=Coordinate(0,1);
    Coordinate derBeta;
    GLdouble _alfa;
	Coordinate P1,P2, Pd1,Pd2;
    Pd1=derivalt(t,r);
    P1=bezier(t);
    P1.x+=-1.0*Pd1.y;
    P1.y+=Pd1.x;
    pData.x=P1.x;
    pData.y=P1.y;
        derBeta=derivalt(t,1);

        if(derBeta.x<0)
            way=Coordinate(0,1);
        else{
            way=Coordinate(0,-1);
            pData.alfa=PI;
        }
        _alfa= derBeta.x * way.x + derBeta.y * way.y;

        pData.alfa+=acos (_alfa);
        //std::cout<<":"<<pData.alfa<<std::endl;

return pData;
}

void Track::finalPoint(){
    Coordinate P0,P1,P2;

    P1=controlPoints[0];
    P2=controlPoints[1];

    P0.x=P1.x - (P2.x - P1.x);
    P0.y=P1.y - (P2.y - P1.y);
    controlPoints.push_back(    Coordinate( P0 )   );
    controlPoints.push_back(    Coordinate( P1 )   );
}

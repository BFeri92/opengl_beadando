#include "Car.h"
#include <iostream>
#include "Game.h"
Car::Car(GLTriangleBatch* _batch, double _horizPosOnTrack, Track& _track) :
	horizPosOnTrack(_horizPosOnTrack), speedChange(0),
	speed(0), positionOnTrack(0), track(_track)
{
	batch = _batch;
	//gltMakeSphere(batch, _horizPosOnTrack, 52, 26);
}

void Car::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	static const GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	M3DMatrix44f vpMatrix;
	m3dMatrixMultiply44(vpMatrix, projectionMatrix, viewMatrix);
	M3DMatrix44f mvpMatrix;
	M3DMatrix44f mMatrix;
	pos.getTransformationMatrix(mMatrix);
	m3dMatrixMultiply44(mvpMatrix, vpMatrix, mMatrix);
	Game::getInstance().getShaderManager().UseStockShader(GLT_SHADER_FLAT, mvpMatrix, vGreen);
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
	batch->Draw();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void Car::step()
{
	speed += speedChange * speedIncPerSec * timer.GetElapsedSeconds();
	if (speed>maxSpeed) speed=maxSpeed;
	if (speed<-1*maxSpeed) speed=-1*maxSpeed;
	positionOnTrack+=speed;
	double integral;
	if (positionOnTrack>1) positionOnTrack=modf(positionOnTrack, &integral); else
	if (positionOnTrack<0) positionOnTrack=1+positionOnTrack;
	pos = track.getCarPosition(positionOnTrack, horizPosOnTrack);
	//std::cout<<positionOnTrack<<" "<<speed<<std::endl;
}

void Car::setSpeedChange(int _speedChange)
{
	std::cout<<"spd"<<_speedChange<<std::endl;
	speedChange=_speedChange;
}

PositionData Car::getPositionData()
{
	return pos;
}

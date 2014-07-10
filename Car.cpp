#include "Car.h"
#include <iostream>
#include "Game.h"
Car::Car(GLTriangleBatch* _batch, double _horizPosOnTrack) :
	horizPosOnTrack(_horizPosOnTrack), speedChange(0),
	speed(0), positionOnTrack(0)
{
	batch = _batch;
	//gltMakeSphere(batch, _horizPosOnTrack, 52, 26);
}

void Car::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	static const GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	M3DMatrix44f mvpMatrix;
	m3dMatrixMultiply44(mvpMatrix, projectionMatrix, viewMatrix);
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
	positionOnTrack=fabs(modf(positionOnTrack, &integral));
	std::cout<<positionOnTrack<<" "<<speed<<std::endl;
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

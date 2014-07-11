#include "Car.h"
#include <iostream>
#include "Game.h"
Car::Car(GLTriangleBatch* _batch, double _horizPosOnTrack, Track& _track, int _textureID, std::string _name) :
	horizPosOnTrack(_horizPosOnTrack), speedChange(0), roundCounter(0),
	speed(0), positionOnTrack(0), track(_track), textureID(_textureID),
	name(_name)
{
	batch = _batch;
	//gltMakeSphere(batch, _horizPosOnTrack, 52, 26);
}

void Car::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	static const GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat vLightPos[] = { 100.0f, 100.0f, 1000.0f, 1.0f };
	M3DVector4f	vLightTransformed;
	m3dTransformVector4(vLightTransformed, vLightPos, viewMatrix);
	M3DMatrix44f vpMatrix;
	m3dMatrixMultiply44(vpMatrix, projectionMatrix, viewMatrix);
	M3DMatrix44f mvMatrix;
	M3DMatrix44f mMatrix;
	pos.getTransformationMatrix(mMatrix);
	m3dMatrixMultiply44(mvMatrix, viewMatrix, mMatrix);
		Game::getInstance().getShaderManager().UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
                                         mvMatrix,
                                         projectionMatrix,
                                         vLightTransformed,
                                         vWhite,
                                         textureID);
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
	batch->Draw();
}

void Car::step()
{
	speed += speedChange * speedIncPerSec * timer.GetElapsedSeconds();
	double decr=0;
	if (speed>0) decr=speedAutoDecPerSec;
	else if (speed<0) decr=-1*speedAutoDecPerSec;
	speed -= decr*timer.GetElapsedSeconds();
	if (speed>maxSpeed) speed=maxSpeed;
	if (speed<-1*maxSpeed) speed=-1*maxSpeed;
	positionOnTrack+=speed;
	double integral;
	if (positionOnTrack>1) {
            positionOnTrack=modf(positionOnTrack, &integral);
            roundCounter++;
            if (roundCounter>3) Game::getInstance().endGame(name);
    } else
	if (positionOnTrack<0) positionOnTrack=1+positionOnTrack;
	pos = track.getCarPosition(positionOnTrack, horizPosOnTrack);
	//std::cout<<positionOnTrack<<" "<<speed<<std::endl;
}

void Car::setSpeedChange(int _speedChange)
{
	speedChange=_speedChange;
}

PositionData Car::getPositionData()
{
	return pos;
}

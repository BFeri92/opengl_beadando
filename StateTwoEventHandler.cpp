#include "StateTwoEventHandler.h"
#include "Game.h"
#include <iostream>

StateTwoEventHandler::StateTwoEventHandler(Car& _car1, Car& _car2) : car1(_car1), car2(_car2)
{
}

void StateTwoEventHandler::keyDownEvent(char key)
{
	keyStates[key]=true;
	if (keyStates['q']) car1.setSpeedChange(Car::FASTER); else
	if (keyStates['a']) car1.setSpeedChange(Car::SLOWER); else
	car1.setSpeedChange(Car::KEEP_SPEED);

	if (keyStates['o']) car2.setSpeedChange(Car::FASTER); else
	if (keyStates['k']) car2.setSpeedChange(Car::SLOWER); else
	car2.setSpeedChange(Car::KEEP_SPEED);
	if (key=='0')
		Game::getInstance().followCar(-1);
	if (key=='1')
		Game::getInstance().followCar(0); else
	if (key=='2')
		Game::getInstance().followCar(1);


}

void StateTwoEventHandler::keyUpEvent(char key)
{
	keyStates[key]=false;
	if (keyStates['q']) car1.setSpeedChange(Car::FASTER); else
	if (keyStates['a']) car1.setSpeedChange(Car::SLOWER); else
	car1.setSpeedChange(Car::KEEP_SPEED);

	if (keyStates['o']) car2.setSpeedChange(Car::FASTER); else
	if (keyStates['k']) car2.setSpeedChange(Car::SLOWER); else
	car2.setSpeedChange(Car::KEEP_SPEED);
}

void StateTwoEventHandler::activeMouseMotionEvent(int x, int y)
{
	//std::cout<<(lastMousePos.y-y)/10.0<<" "<<(lastMousePos.x-x)/10.0<<std::endl;
	Game::getInstance().moveCameraFwd((lastMousePos.y-y)/5.0);
	Game::getInstance().moveCameraRight((lastMousePos.x-x)/10.0);
	lastMousePos = Coordinate(x,y);

}
void StateTwoEventHandler::mouseUpEvent(int button, int x, int y)
{

}
void StateTwoEventHandler::mouseDownEvent(int button, int x, int y)
{
//	std::cout<<"mp"<<std::endl;
	lastMousePos = Coordinate(x,y);
}


#include "StateTwoEventHandler.h"
#include "Game.h"
#include <iostream>

StateTwoEventHandler::StateTwoEventHandler()
{
}

void StateTwoEventHandler::keyDownEvent(char key) 
{
	
}

void StateTwoEventHandler::keyUpEvent(char key) 
{
	
}

void StateTwoEventHandler::activeMouseMotionEvent(int x, int y) 
{
	std::cout<<(lastMousePos.y-y)/100.0<<" "<<(lastMousePos.x-x)/100.0<<std::endl;
	Game::getInstance().moveCameraFwd((lastMousePos.y-y)/100.0);
	Game::getInstance().moveCameraRight((lastMousePos.x-x)/100.0);
	lastMousePos = Coordinate(x,y);
	
}
void StateTwoEventHandler::mouseUpEvent(int button, int x, int y) 
{
	
}
void StateTwoEventHandler::mouseDownEvent(int button, int x, int y) 
{
	std::cout<<"mp"<<std::endl;
	lastMousePos = Coordinate(x,y);
}


#include "StateOneEventHandler.h"
#include "Game.h"
#include "Coordinate.h"
#include <iostream>


StateOneEventHandler::StateOneEventHandler(Track& _track) : track(_track)
{
	selectedPoint=-1;
	acceptNewPoints=true;
}

void StateOneEventHandler::keyDownEvent(char key) 
{
}

void StateOneEventHandler::keyUpEvent(char key) 
{
	if (key==' ')
	{
		if (acceptNewPoints)
		{
			track.finalPoint();
			Game::getInstance().updateTrackBatches();
			acceptNewPoints=false;
		} else {
			Game::getInstance().initStateTwo();
		}
	}
}

void StateOneEventHandler::activeMouseMotionEvent(int x, int y) 
{
	if (selectedPoint!=-1){
		 track.setControlPointAtIndex(selectedPoint, Coordinate(x, Game::winHeight-y));
		 Game::getInstance().updateTrackBatches();
	 }
}

void StateOneEventHandler::mouseUpEvent(int button, int x, int y) 
{
	if (selectedPoint!=-1) {
		track.setControlPointAtIndex(selectedPoint, Coordinate(x, Game::winHeight-y));
		Game::getInstance().updateTrackBatches();
	}
	else if (acceptNewPoints) {
		track.addControlPoint(Coordinate(x, Game::winHeight-y));
		Game::getInstance().updateTrackBatches();
	}
	selectedPoint=-1;
}

void StateOneEventHandler::mouseDownEvent(int button, int x, int y) 
{
	selectedPoint=track.getControlPointIndexAt(Coordinate(x, Game::winHeight-y), 10);
}



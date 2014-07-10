#ifndef STATETWOEVENTHANDLER_H_INCLUDED
#define STATETWOEVENTHANDLER_H_INCLUDED

#include "Coordinate.h"
#include "EventHandler.h"
#include "Car.h"
#include <map>

class StateTwoEventHandler : public EventHandler{
	private:
		Coordinate lastMousePos;
		Car& car1;
		Car& car2;
		std::map<char,bool> keyStates;
	public:
		StateTwoEventHandler(Car& _car1, Car& _car2);
		virtual void keyDownEvent(char key);
		virtual void keyUpEvent(char key);
		virtual void activeMouseMotionEvent(int x, int y);
		virtual void mouseUpEvent(int button, int x, int y);
		virtual void mouseDownEvent(int button, int x, int y);
};
#endif

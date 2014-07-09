#ifndef STATETWOEVENTHANDLER_H_INCLUDED
#define STATETWOEVENTHANDLER_H_INCLUDED

#include "Coordinate.h"
#include "EventHandler.h"

class StateTwoEventHandler : public EventHandler{
	private:
		Coordinate lastMousePos;
		//bool mouseDown;
	public:
		StateTwoEventHandler();
		virtual void keyDownEvent(char key);
		virtual void keyUpEvent(char key);
		virtual void activeMouseMotionEvent(int x, int y);
		virtual void mouseUpEvent(int button, int x, int y);
		virtual void mouseDownEvent(int button, int x, int y);
};
#endif

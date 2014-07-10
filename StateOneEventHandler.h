#ifndef STATEONEEVENTHANDLER_H_INCLUDED
#define STATEONEEVENTHANDLER_H_INCLUDED

#include "EventHandler.h"

class StateOneEventHandler : public EventHandler{
	private:

	public:
		StateOneEventHandler();
		virtual void keyDownEvent(char key);
		virtual void keyUpEvent(char key);
		virtual void activeMouseMotionEvent(int x, int y);
		virtual void mouseUpEvent(int button, int x, int y);
		virtual void mouseDownEvent(int button, int x, int y);
};
#endif

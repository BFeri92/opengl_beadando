#ifndef STATEONEEVENTHANDLER_H_INCLUDED
#define STATEONEEVENTHANDLER_H_INCLUDED

#include "EventHandler.h"
#include "Track.h"

class StateOneEventHandler : public EventHandler{
	private:
		int selectedPoint;
		Track& track;
		bool acceptNewPoints;
	public:
		StateOneEventHandler(Track& _track);
		virtual void keyDownEvent(char key);
		virtual void keyUpEvent(char key);
		virtual void activeMouseMotionEvent(int x, int y);
		virtual void mouseUpEvent(int button, int x, int y);
		virtual void mouseDownEvent(int button, int x, int y);
};
#endif

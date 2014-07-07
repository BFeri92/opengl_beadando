#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED
class EventHandler{
	public:
		virtual void keyDownEvent(char key) = 0;
		virtual void keyUpEvent(char key) = 0;
		virtual void activeMouseMotionEvent(int x, int y) = 0;
		virtual void mouseUpEvent(int button, int x, int y) = 0;
		virtual void mouseDownEvent(int button, int x, int y) = 0;
};
#endif

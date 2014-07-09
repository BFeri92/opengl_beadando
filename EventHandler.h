#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED
class EventHandler{
	public:
		virtual void keyDownEvent(char key);
		virtual void keyUpEvent(char key);
		virtual void activeMouseMotionEvent(int x, int y);
		virtual void mouseUpEvent(int button, int x, int y);
		virtual void mouseDownEvent(int button, int x, int y);
};
#endif

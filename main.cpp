#include "AbstractObjLoader.h"
#include "Game.h"
#include <GLTools.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#ifndef __WIN32__
#define FREEGLUT_STATIC
#endif
#include <GL/glut.h>
#endif


void SetupRC(void)
{
}


void RenderScene(void)
{
	Game::getInstance().render();
}

void ShutdownRC(void)
{
}

void ChangeSize(int w, int h)
{
}

void onClick(int button, int state, int x, int y)
{
	if (state==GLUT_DOWN)
	{
		Game::getInstance().getEventHandler().mouseDownEvent(button,x,y);
	} else if (state==GLUT_UP)
	{
		Game::getInstance().getEventHandler().mouseUpEvent(button,x,y);
	}
}

void onMouseMove(int x, int y)
{
	Game::getInstance().getEventHandler().activeMouseMotionEvent(x,y);
	glutPostRedisplay();
}

void KeyPressFunc(unsigned char key, int x, int y)
{
	Game::getInstance().getEventHandler().keyDownEvent(key);
}

void onKeyUp(unsigned char key, int x, int y)
{
	Game::getInstance().getEventHandler().keyUpEvent(key);
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(KeyPressFunc);
    glutKeyboardUpFunc(onKeyUp);
	glutMotionFunc(onMouseMove);
	glutMouseFunc(onClick);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    SetupRC();
    glutMainLoop();
    ShutdownRC();
    return 0;
}

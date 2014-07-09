#include "AbstractObjLoader.h"
#include "Game.h"
#include <GLTools.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
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

void KeyPressFunc(unsigned char key, int x, int y)
{
	Game::getInstance().getEventHandler().keyDownEvent(key);
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

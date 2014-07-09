#include "Game.h"

#include <vector>
#include <math3d.h>
#include "Sphere.h"
#include "EventHandler.h"
#include <iostream>
#include <glut.h>

Game* Game::instance = 0;

Game::Game() : eventHandler(0)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	GLFrustum viewFrustum;
    viewFrustum.SetPerspective(35.0f, 800.0/600.0, .005f, 5000.0f);
	//viewFrustum.SetOrthographic(-10, 10,-10 , 10, -10, 10);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f );
	objectsToDraw.push_back(new Sphere());
	camera.MoveForward(-10);
}

Game::~Game()
{
	if (eventHandler!=0)
	{
		delete eventHandler;
	}
	for (std::vector<Drawable*>::iterator i = objectsToDraw.begin(); i!=objectsToDraw.end(); i++)
	{
		delete *i;
	}
}

Game& Game::getInstance()
{
	if (!Game::instance) {
		Game::instance = new Game();
	}
	return *Game::instance;
}

void Game::initStateOne()
{
}

void Game::initStateTwo()
{
}

void Game::render()
{
	std::cout<<"render"<<std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLMatrixStack viewMatrix;
    M3DMatrix44f mCamera;
    camera.GetCameraMatrix(mCamera);
    viewMatrix.LoadMatrix(mCamera);
    for (int i=0; i<4; i++)
    {
		for (int j=0; j<4; j++)
			std::cout<<mCamera[i*4+j]<<" ";
	std::cout<<std::endl;
	}
    //viewMatrix.LoadIdentity();
    //projectionMatrix.LoadIdentity();
    //viewMatrix.Translate(1,0,0);
    for (std::vector<Drawable*>::iterator i = objectsToDraw.begin(); i!=objectsToDraw.end(); i++)
    {
		(*i)->paint(viewMatrix.GetMatrix(), projectionMatrix.GetMatrix());
	}
    glutSwapBuffers();
    //glutPostRedisplay();
}

EventHandler& Game::getEventHandler()
{
	return *eventHandler;
}

void Game::moveCameraFwd()
{
}

void Game::moveCameraBack()
{
}

void Game::moveCameraRight()
{
}

void Game::moveCameraLeft()
{
}

void Game::followCar(int id)
{
}
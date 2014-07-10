#include "Game.h"

#include <vector>
#include <math3d.h>
#include "Sphere.h"
#include "MeshTest.h"
#include "ObjLoader.h"
#include "EventHandler.h"
#include "StateOneEventHandler.h"
#include "StateTwoEventHandler.h"
#include "Track_d.h"
#include "TrackBatch.h"
#include <iostream>
#include <glut.h>
#include <GLTriangleBatch.h>

Game* Game::instance = 0;

Game::Game() : eventHandler(new EventHandler)
{
	shaderManager.InitializeStockShaders();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f );
    //glEnable(GL_CULL_FACE);
//	initStateTwo();
	camera.MoveForward(-10);
	GLFrustum viewFrustum;
    viewFrustum.SetPerspective(35.0f, 800.0/600.0, .005f, 5000.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	ObjLoader loader;
    MeshTest* asd=new MeshTest(loader.getBatch("car.obj"));
	objectsToDraw.push_back(asd);
	Car* car1=new Car(0,0);
	Car* car2=new Car(0,0);
	/*
	objectsToDraw.push_back(car1);
	objectsToDraw.push_back(car2);*/
	
	eventHandler = new StateTwoEventHandler(*car1,*car2);

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
	projectionMatrix.LoadIdentity();
	delete eventHandler;
	eventHandler = new StateOneEventHandler();
}

void Game::initStateTwo()
{
	camera.MoveForward(-10);
	GLFrustum viewFrustum;
    viewFrustum.SetPerspective(35.0f, 800.0/600.0, .005f, 5000.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	delete eventHandler;
	
	GLTriangleBatch* sphere = new GLTriangleBatch();
	gltMakeSphere(*sphere, 1.0f, 52, 26);
	GLTriangleBatch* sphere2 = new GLTriangleBatch();
	gltMakeSphere(*sphere2, 10.0f, 52, 26);
	TrackBatch* tb = new TrackBatch(track);
	objectsToDraw.push_back(tb);
	Car* car1=new Car(sphere,0,track);
	Car* car2=new Car(sphere2,0,track);
	cars.push_back(car1);
	cars.push_back(car2);
	objectsToDraw.push_back(car1);
	objectsToDraw.push_back(car2);
	
	eventHandler = new StateTwoEventHandler(*car1,*car2);
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLMatrixStack viewMatrix;
    M3DMatrix44f mCamera;
    camera.GetCameraMatrix(mCamera);
    viewMatrix.LoadMatrix(mCamera);
    /*
    for (int i=0; i<4; i++)
    {
		for (int j=0; j<4; j++)
			std::cout<<mCamera[i*4+j]<<" ";
	std::cout<<std::endl;
	}*/
    //viewMatrix.LoadIdentity();
    //projectionMatrix.LoadIdentity();
    //viewMatrix.Translate(1,0,0);
    for (std::vector<Drawable*>::iterator i = objectsToDraw.begin(); i!=objectsToDraw.end(); i++)
    {
		(*i)->paint(viewMatrix.GetMatrix(), projectionMatrix.GetMatrix());
	}
    glutSwapBuffers();
        for (std::vector<Car*>::iterator i = cars.begin(); i!=cars.end(); i++)
    {
		(*i)->step();
	}
    glutPostRedisplay();
}

EventHandler& Game::getEventHandler()
{
	return *eventHandler;
}

void Game::moveCameraFwd(float amount)
{
	camera.MoveForward(amount);
}

void Game::moveCameraBack(float amount)
{
	camera.MoveForward(-amount);
}

void Game::moveCameraRight(float amount)
{
	camera.MoveRight(amount);
}

void Game::moveCameraLeft(float amount)
{
	camera.MoveRight(-amount);
}

void Game::followCar(int id)
{
}

GLShaderManager& Game::getShaderManager()
{
	return shaderManager;
}

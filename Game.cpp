#include "Game.h"

#include <vector>
#include <math3d.h>
#include "Sphere.h"
#include "MeshTest.h"
#include "ObjLoader.h"
#include "Sky.h"
#include "EventHandler.h"
#include "StateOneEventHandler.h"
#include "StateTwoEventHandler.h"
#include <iostream>
#include <GL/glut.h>
#include <GLTriangleBatch.h>

Game* Game::instance = 0;

Game::Game() : eventHandler(new EventHandler)
{
	shaderManager.InitializeStockShaders();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f );
    
    glGenTextures(5, textures);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    LoadTGATexture("asph.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    LoadTGATexture("car.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    LoadTGATexture("car2.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    LoadTGATexture("grass.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    LoadTGATexture("sky.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);


	initStateOne();
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
    glDeleteTextures(5, textures);
} 

void Game::updateTrackBatches()
{
    trackBatch->update(track);
    trackPointsBatch->update(track);
    glutPostRedisplay();
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
	glDisable(GL_CULL_FACE);
    for (std::vector<Drawable*>::iterator i = objectsToDraw.begin(); i!=objectsToDraw.end(); i++)
    {
		delete *i;
	}
	objectsToDraw.clear();
	GLFrustum viewFrustum;
    viewFrustum.SetOrthographic(0, winWidth, 0, winHeight, 1, -1);
    
    M3DMatrix44f transpose = {	1, 0, 0, 0,
								0, 0, 1, 0, 
								0, 1, 0, 0, 
								0, 0, 0, 1};
								
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    projectionMatrix.MultMatrix(transpose);
    trackBatch = new TrackBatch(track);
    trackPointsBatch = new TrackPointsBatch(track);
	objectsToDraw.push_back(trackBatch);
	objectsToDraw.push_back(trackPointsBatch);
	delete eventHandler;
	eventHandler = new StateOneEventHandler(track);
}

void Game::initStateTwo()
{
	//glEnable(GL_CULL_FACE);
    for (std::vector<Drawable*>::iterator i = objectsToDraw.begin(); i!=objectsToDraw.end(); i++)
    {
		delete *i;
	}
	objectsToDraw.clear();
	PositionData initialCamPos = track.getCarPosition(0,0);
	std::cout<<initialCamPos.y<<".."<<initialCamPos.x<<std::endl;
	camera.SetOrigin(initialCamPos.x, 40, initialCamPos.y);
	camera.MoveForward(-200);
	GLFrustum viewFrustum;
    viewFrustum.SetPerspective(35.0f, float(winWidth)/float(winHeight), .005f, 5000.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	delete eventHandler;
	ObjLoader loader;
	TrackBatch* tb = new TrackBatch(track);
	objectsToDraw.push_back(tb);
	Car* car1=new Car(loader.getBatch("car.obj"),-10,track, 1);
	Car* car2=new Car(loader.getBatch("car2.obj"),10,track, 2);
	cars.push_back(car1);
	cars.push_back(car2);
	objectsToDraw.push_back(car1);
	objectsToDraw.push_back(car2);
    
	Grass* grass=new Grass(3);
	objectsToDraw.push_back(grass);
	objectsToDraw.push_back(new Sky(4));
	
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
	//camera.MoveRight(amount);
	camera.RotateWorld(amount*0.01f, 0.0f, 1.0f, 0.0f);
}

void Game::moveCameraLeft(float amount)
{
	camera.RotateWorld(-amount*0.01f, 0.0f, 1.0f, 0.0f);
}

void Game::followCar(int id)
{
}

GLShaderManager& Game::getShaderManager()
{
	return shaderManager;
}

bool Game::LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;
	
	// Read the texture bits
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if(pBits == NULL) 
		return false;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
				 eFormat, GL_UNSIGNED_BYTE, pBits);
	
    free(pBits);
    
    if(minFilter == GL_LINEAR_MIPMAP_LINEAR || 
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);
    
	return true;
}

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <vector>

#include "EventHandler.h"
#include "Drawable.h"
#include "Car.h"
#include "Grass.h"
#include "Track.h"
#include "TrackBatch.h"
#include "TrackPointsBatch.h"
#include <string>

class Game{
	private:
		GLShaderManager shaderManager;
		EventHandler* eventHandler;
		std::vector<Car*> cars;
		std::vector<Drawable*> objectsToDraw;
		TrackBatch* trackBatch;
		TrackPointsBatch* trackPointsBatch;
		static Game* instance;
		GLFrame camera;
		GLMatrixStack projectionMatrix;
		Game();
		~Game();
		Track track;
		GLuint textures[5];
		bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
		int carToFollow;
	public:
		static const int winWidth=800;
		static const int winHeight=600;
		static Game& getInstance();
		void updateTrackBatches();
		void initStateOne();
		void initStateTwo();
		void render();
		EventHandler& getEventHandler();
		void moveCameraFwd(float amount);
		void moveCameraBack(float amount);
		void moveCameraRight(float amount);
		void moveCameraLeft(float amount);
		void followCar(int id);
		GLShaderManager& getShaderManager();
		void endGame(std::string nev);
};
#endif

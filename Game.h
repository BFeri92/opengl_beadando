#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <vector>

#include "EventHandler.h"
#include "Drawable.h"
#include "Car.h"

class Game{
	private:
		GLShaderManager shaderManager;
		EventHandler* eventHandler;
		std::vector<Car*> cars;
		std::vector<Drawable*> objectsToDraw;
		static Game* instance;
		GLFrame camera;
		GLMatrixStack projectionMatrix;
		Game();
		~Game();
	public:
		static Game& getInstance();
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
};
#endif

#include "Game.h"

#include <vector>

#include "EventHandler.h"

Game* Game::instance = 0;

Game::Game() : eventHandler(0)
{
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

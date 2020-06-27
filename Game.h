#pragma once

#include <iostream>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

/*
	Class that acts as the game engine.
	wrapper class.
*/

using namespace sf;

class Game
{
private:
	// variables
	// window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	bool endGame;

	Player player;

	Ball ball;

	std::vector<Enemy*> enemies;

	// private functions
	void initVariables();
	void initWindow();

public:
	// constructors / destructors
	Game();
	virtual ~Game();

	// accessors
	const bool running() const;

	// functions
	void pollEvents();
	void updateInput();
	void spawnEnemies();
	void updatePlayerWindowCollision();
	void updateBallWindowCollision();
	void playerBallCollision();
	void enemiesBallCollision();

	void update();
	void render();
};


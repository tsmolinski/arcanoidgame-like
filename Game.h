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
	//variables
	//window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	bool endGame;

	Player player;

	Ball ball;

	std::vector<Enemy*> enemies;
	//int blockX;
	//int blockY;
	//int countBlock;
	//int maxBlocks;

	//private functions
	void initVariables();
	void initWindow();

public:
	//constructors / destructors
	Game();
	virtual ~Game();

	//accessors
	const bool running() const;

	//functions
	void pollEvents();

	void spawnEnemies();

	void playerBallCollision();
	void enemiesBallCollision();

	void update();
	void render();
};


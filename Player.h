#pragma once

//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//
//using namespace sf;

#include "Enemy.h"

class Player
{

private:
	RectangleShape shape;

	float movementSpeed;


	void initVariables();
	void initShape();

public:
	Player(float x = 350.f, float y = 550.f);
	virtual ~Player();

	FloatRect playerBounds();

	void updateInput();
	void updateWindowBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};


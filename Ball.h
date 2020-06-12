#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Ball
{
private: 
	CircleShape shape;

	const float ballVelocity{ 4.f };
	Vector2f velocity{ballVelocity, ballVelocity};

	void initVariables();
	void initShape();

public:
	Ball(float x = 200.f, float y = 30.f);
	virtual ~Ball();

	const FloatRect ballBounds() const;

	// ball move (for collision with paddle and enemies)
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// functions
	void updateWindowBoundsCollision();
	void update();
	void render(RenderTarget& target);
	
};


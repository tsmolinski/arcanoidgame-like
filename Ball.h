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

	const float ballVelocity{ 7.f };
	Vector2f velocity{ballVelocity, ballVelocity};

	void initVariables();
	void initShape();

public:
	Ball(float x = 300.f, float y = 200.f);
	virtual ~Ball();

	// accessors
	const FloatRect ballBounds() const;
	const Vector2f& getPosition() const;

	// ball move (for paddle and enemies collision)
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// functions
	void move(const float dir_x, const float dir_y);
	void update();
	void render(RenderTarget& target);
	
};


#include "Ball.h"

#include <iostream>

void Ball::initVariables()
{
}

void Ball::initShape()
{
	shape.setFillColor(Color::Cyan);
	shape.setRadius(12.f);
}

Ball::Ball(float x, float y)
{
	shape.setPosition(x, y);

	initShape();
	initVariables();
}

Ball::~Ball()
{

}

const FloatRect Ball::ballBounds() const
{
	return shape.getGlobalBounds();
}

// ball move (for collision with paddle and enemies)
void Ball::moveLeft()
{
	velocity.x = -ballVelocity;
}

void Ball::moveRight()
{
	velocity.x = ballVelocity;
}

void Ball::moveUp()
{
	velocity.y = -ballVelocity;
}

void Ball::moveDown()
{
	velocity.y = ballVelocity;
}

void Ball::move(const float dir_x, const float dir_y)
{
	return shape.move(dir_x, dir_y);
}

void Ball::update()
{
	shape.move(velocity);
}

void Ball::render(RenderTarget& target)
{
	target.draw(shape);
}

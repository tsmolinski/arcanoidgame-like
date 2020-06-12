#include "Ball.h"

#include <iostream>

void Ball::initVariables()
{
	//ballVelocity = 5.f;
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

void Ball::updateWindowBoundsCollision()
{
	shape.move(velocity);
	/*shape.move(4, 0);*/
	if (shape.getGlobalBounds().left <= 0)													// left
		velocity.x = ballVelocity;	//shape.move(velocity.x, shape.getPosition().y);

	else if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= 800)			// right
		velocity.x = -ballVelocity;

	else if (shape.getGlobalBounds().top <= 0)												// top
		velocity.y = ballVelocity;

	else if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= 600)			// bottom
		velocity.y = -ballVelocity;
}

void Ball::update()
{
	updateWindowBoundsCollision();
}

void Ball::render(RenderTarget& target)
{
	target.draw(shape);
}

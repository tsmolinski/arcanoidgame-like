#include "Player.h"


void Player::initVariables()
{
	movementSpeed = 10.f;
}

void Player::initShape()
{
	shape.setFillColor(Color::Green);
	shape.setSize(Vector2f(140.f, 30.f));

}

Player::Player(float x, float y)
{
	shape.setPosition(x, y);

	initVariables();
	initShape();
}

Player::~Player()
{

}

FloatRect Player::playerBounds()
{
	return shape.getGlobalBounds();
}

void Player::updateInput()
{
	//keyboard input
	//left / right
	if (Keyboard::isKeyPressed(Keyboard::A) | Keyboard::isKeyPressed(Keyboard::Left))
	{
		shape.move(-movementSpeed, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) | Keyboard::isKeyPressed(Keyboard::Right))
	{
		shape.move(movementSpeed, 0.f);
	}
}

void Player::updateWindowBoundsCollision(const RenderTarget* target)
{
	// left
	if (shape.getGlobalBounds().left <= 0.f)
		shape.setPosition(0.f, shape.getGlobalBounds().top);
	// right
	else if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x)
		shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);

}

void Player::update(const RenderTarget* target)
{
	updateInput();

	// player and window bounds collision
	updateWindowBoundsCollision(target);
}

void Player::render(RenderTarget* target)
{
	target->draw(shape);
}

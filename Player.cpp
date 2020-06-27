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

// accessors
const FloatRect Player::playerBounds() const
{
	return shape.getGlobalBounds();
}

const Vector2f& Player::getPosition() const
{
	return shape.getPosition();
}

// modifiers
void Player::setPosition(const float x, const float y)
{
	shape.setPosition(x, y);
}

// functions
void Player::move(const float dir_x, const float dir_y)
{
	shape.move(movementSpeed * dir_x, movementSpeed * dir_y);
}

void Player::update()
{
}

void Player::render(RenderTarget* target)
{
	target->draw(shape);
}

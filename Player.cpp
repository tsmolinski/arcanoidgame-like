#include "Player.h"


void Player::initVariables()
{
	movementSpeed = 11.f;
}

void Player::initShape()
{
	shape.setFillColor(Color::Green);

	float shape_width = 140.f;
	float shape_height = 30.f;
	shape.setSize(Vector2f(shape_width, shape_height));

	//shape.setOrigin(shape_width / 2, shape_height / 2);


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

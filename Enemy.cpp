#include "Enemy.h"

// private
void Enemy::initShape()
{
	shape.setFillColor(Color::Yellow);
	shape.setSize(Vector2f(60.f, 20.f));

}

// public
Enemy::Enemy(float x, float y)
{
	shape.setPosition(x, y);
	initShape();
}

Enemy::~Enemy()
{

}

// accessors
const FloatRect Enemy::enemyBounds() const
{
	return shape.getGlobalBounds();
}

// functions
void Enemy::update()
{

}

void Enemy::render(RenderTarget& target)
{
	target.draw(shape);
}

#include "Enemy.h"

// private
void Enemy::initShape() //void Enemy::initShape(const RenderWindow& window)
{
	shape.setFillColor(Color::Yellow);
	shape.setSize(Vector2f(60.f, 20.f));

}

// public
Enemy::Enemy(float x, float y)  //Enemy::Enemy(const RenderWindow& window)
{
	shape.setPosition(x, y);
	initShape();   //initShape(window);
}

Enemy::~Enemy()
{

}

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

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Enemy
{
private:
	RectangleShape shape;

	void initShape(); //void initShape(const RenderWindow& window); 

public:
	Enemy(float x, float y); //Enemy(const RenderWindow& window);
	virtual ~Enemy();

	const FloatRect enemyBounds() const;

	// functions
	void update();
	void render(RenderTarget& target);

};


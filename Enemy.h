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

	void initShape(); 

public:
	Enemy(float x, float y);
	virtual ~Enemy();

	// accessors
	const FloatRect enemyBounds() const;

	// functions
	void update();
	void render(RenderTarget& target);

};


#include "Game.h"

// private functions
void Game::initVariables()
{
	window = nullptr;

	endGame = false;
}

void Game::initWindow()
{
	videoMode = VideoMode(800, 600);
	window = new RenderWindow(videoMode, "Arcanoid Game", Style::Titlebar | Style::Close);
	window->setFramerateLimit(60);

}

// constructors / destructors
Game::Game()
{
	initVariables();
	initWindow();
}

Game::~Game()
{
	delete window;

	// delete enemies
	for (auto* i : enemies)
	{
		delete i;
	}
}

// accessors
const bool Game::running() const
{
	return window->isOpen();
}

// functions
void Game::pollEvents()
{
	// event polling
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			if (ev.key.code == Keyboard::Escape)
				window->close();
			break;
		}
	}
}

void Game::updateInput()
{
	//keyboard input
	//left / right
	if (Keyboard::isKeyPressed(Keyboard::A) | Keyboard::isKeyPressed(Keyboard::Left))
	{
		player.move(-1.f, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) | Keyboard::isKeyPressed(Keyboard::Right))
	{
		player.move(1.f, 0.f);
	}
}

void Game::spawnEnemies()
{

	int posX = 60, posY = 20;
	int blockX = 10;
	int blockY = 5;
	int maxBlocks = 50;
	//int countBlock = 0;


	for (int j = 0; j < blockY; j++)
	{

		for (int i = 0; i < blockX; i++)
		{
			if (enemies.size() < maxBlocks)
			{
				enemies.push_back(new Enemy(((i + 1) * (posX + 10)), ((j + 1) * (posY + 10))));
				//std::cout << "Enemy size: " << enemies.size() << "\n";
				//std::cout << "enemy #" << i << " bound top: " << enemies[i].enemyBounds().top << "\n";
				//countBlock++;
				//std::cout << "countBlock: " << countBlock << "\n";
			}
		}
	}
	//std::cout << "enemy 30" << " bound top: " << enemies[29].enemyBounds().top << "\n";
}

void Game::updatePlayerWindowCollision()
{
	// left
	if (player.playerBounds().left <= 0.f)
	{
		player.setPosition(0.f, player.playerBounds().top);
	}
	// right
	else if (player.playerBounds().left + player.playerBounds().width >= window->getSize().x)
	{
		player.setPosition(window->getSize().x - player.playerBounds().width, player.playerBounds().top);
	}
}

void Game::updateBallWindowCollision()
{
		if (ball.ballBounds().left <= 0)
		{
			ball.moveRight();
		}

		else if (ball.ballBounds().left + ball.ballBounds().width >= window->getSize().x)
		{
			ball.moveLeft();
		}

		if (ball.ballBounds().top <= 0)
		{
			ball.moveDown();
		}

		else if (ball.ballBounds().top + ball.ballBounds().height >= window->getSize().y)
		{
			ball.moveUp();
		}
}

void Game::playerBallCollision()
{
	if (player.playerBounds().intersects(ball.ballBounds()) &&
		ball.getPosition().x < player.getPosition().x)
	{
		ball.moveUp();
		ball.moveLeft();
	}

	else if (player.playerBounds().intersects(ball.ballBounds()) &&
		ball.getPosition().x > player.getPosition().x)
	{
		ball.moveUp();
		ball.moveRight();
	}
}

void Game::enemiesBallCollision()
// gora -- dol wydaje sie dzialac dobrze (cos i tak nie dziala)
// zle dziala na boki, dlaczego nie dziala odbijanie od lewej??? pilka idzie tylko --> (zmienic w ball.cpp)
// nie wiem, dlaczego tak dziala
// change ball coordinates -> ball,h (constructor)
// change ball dir -> Ball::update()
{
//	for (int i = 0; i < enemies.size(); ++i)
//	{
//		bool enemy_removed = false;
//		if (ball.ballBounds().intersects(enemies[i]->enemyBounds()))
//		{
//			//if ((ball.ballBounds().top <= (enemies[i]->enemyBounds().top + enemies[i]->enemyBounds().height) && !enemy_removed))
//			//{
//			//	ball.moveDown();
//			//	enemies.erase(enemies.begin() + i);
//			//	bool enemy_removed = true;
//			//}
//				if (((ball.ballBounds().top + ball.ballBounds().height) >= enemies[i]->enemyBounds().top) && !enemy_removed)
//				{
//					ball.moveUp();
//					enemies.erase(enemies.begin() + i);
//					bool enemy_removed = true;
//				}
//
//			//enemies.erase(enemies.begin() + i);
//			//std::cout << enemies.size() << "\n";
//
//			//if ((ball.ballBounds().left + ball.ballBounds().width) >= enemies[i].enemyBounds().left)
//			//{
//			//	ball.moveLeft();
//			//	enemies.erase(enemies.begin() + i);
//			//}
//
//			//if (ball.ballBounds().left <= enemies[i].enemyBounds().left + enemies[i].enemyBounds().width)
//			//{
//			//	ball.moveRight();
//			//	enemies.erase(enemies.begin() + i);
//			//}
//
//		}
//	}
}

void Game::update()
{
	updateInput();
	pollEvents();
	ball.update();
	updatePlayerWindowCollision();
	updateBallWindowCollision();
	spawnEnemies();
	playerBallCollision();
	enemiesBallCollision();
}

void Game::render()
{
	/*
		-clear old frame,
		-render objects,
		-display frame in window

		Renders the game objects.
	*/

	window->clear();

	//draw game objects
	player.render(window);

	for (auto* i : enemies)
	{
		i->render(*window);
	}

	ball.render(*window);

	window->display();
}

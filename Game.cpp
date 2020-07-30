#include <cmath>

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

void Game::initGUI()
{
	// load font
	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font pixellettersfull" << "\n";
	}

	// init game over text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(
		window->getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
		window->getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f);
}

// constructors / destructors
Game::Game()
{
	initVariables();
	initWindow();
	initGUI();
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

void Game::run()
{
	while (window->isOpen())
	{
		pollEvents();

		if (ball.ballBounds().top + ball.ballBounds().height < window->getSize().y)
		{
			update();
		}
		render();
	}
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
			}
		}
	}
}

void Game::updatePlayerWindowCollision()
{
	// left
	if (player.playerBounds().left <= 0.f)
	{
		player.setPosition(0.f, player.getPosition().y);
	}
	// right
	else if (player.playerBounds().left + player.playerBounds().width >= window->getSize().x)
	{
		player.setPosition(window->getSize().x - player.playerBounds().width, player.getPosition().y);
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
	// paddle origin is in top left corner, the paddle width is 140.f, 70.f is the middle of the paddle
	if (player.playerBounds().intersects(ball.ballBounds()) &&
		ball.getPosition().x < player.getPosition().x + player.playerBounds().width / 2)
	{
		ball.moveUp();
		ball.moveLeft();
	}

	if (player.playerBounds().intersects(ball.ballBounds()) &&
		ball.getPosition().x > player.getPosition().x + player.playerBounds().width / 2)
	{
		ball.moveUp();
		ball.moveRight();
		std::cout << "player: " << player.getPosition().x << "\n";
		std::cout << "ball: " << ball.getPosition().x << "\n";
	}
}

void Game::enemiesBallCollision()
// change ball coordinates -> ball,h (constructor)
// change ball dir -> Ball::update()
{
	bool enemy_removed = false;
	for (int i = 0; i < enemies.size() && !enemy_removed; i++)
	{
		if (ball.ballBounds().intersects(enemies[i]->enemyBounds()))
		{
			// if Ball(bottom) - Block(top) < Block(bottom) - Ball(top) than we hit the block from the top
			bool ballFromTop(std::abs((ball.ballBounds().top + ball.ballBounds().height) - (enemies[i]->enemyBounds().top)) <
							 std::abs((enemies[i]->enemyBounds().top + enemies[i]->enemyBounds().height) - ball.ballBounds().top));

			// if Ball(right) - Block(left) < Block(right) - Ball(left) than we hit the block from the left
			bool ballFromLeft(std::abs((ball.ballBounds().left + ball.ballBounds().width) - enemies[i]->enemyBounds().left) <
							  std::abs((enemies[i]->enemyBounds().left + enemies[i]->enemyBounds().width) - ball.ballBounds().left));

			// if minOverlapVertically is less than minOverlapHorizontally, we hit the block vertically
			float minOverlapVertically{
				ballFromTop ?
				(ball.ballBounds().top + ball.ballBounds().height - enemies[i]->enemyBounds().top) :
				(enemies[i]->enemyBounds().top + enemies[i]->enemyBounds().height - ball.ballBounds().top)
			};

			// if minOverlapHorizontally is less than minOverlapVertically, we hit the block horizontally <-->
			float minOverlapHorizontally{
				ballFromLeft ?
				(ball.ballBounds().left + ball.ballBounds().width - enemies[i]->enemyBounds().left) :
				(enemies[i]->enemyBounds().left + enemies[i]->enemyBounds().width - ball.ballBounds().left)
			};

			if (std::abs(minOverlapVertically) < std::abs(minOverlapHorizontally))
			{
				if (ballFromTop)
				{
					ball.moveUp();
					enemies.erase(enemies.begin() + i);
					enemy_removed = true;
				}
				else
				{
					ball.moveDown();
					enemies.erase(enemies.begin() + i);
					enemy_removed = true;
				}
			}
			else if (std::abs(minOverlapHorizontally) < std::abs(minOverlapVertically))
			{
				if (ballFromLeft)
				{
					ball.moveLeft();
					enemies.erase(enemies.begin() + i);
					enemy_removed = true;
				}
				else
				{
					ball.moveRight();
					enemies.erase(enemies.begin() + i);
					enemy_removed = true;
				}
			}
		}
	}
}

void Game::update()
{
	updateInput();
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

	// game over text screen
	if (ball.ballBounds().top + ball.ballBounds().height > window->getSize().y)
	{
		window->draw(gameOverText);
	}


	window->display();
}

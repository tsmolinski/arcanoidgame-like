#include "Game.h"


//using namespace sf;

int main()
{
	//init game engine
	Game game;

	//game loop
	while (game.running())
	{
		//update
		game.update();

		//render
		game.render();
	}

	//end of application
	return 0;
}
#include "Game/Game.h"

int main()
{
	Game* game = new Game(800, 600);

	game->Run();

	delete game;
}
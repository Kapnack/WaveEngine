#include "Engine/Game/Game.h"
#include "Entity/Entity2D/Shape/Square/Square.h"

int main()
{
	Game* game = new Game(800, 600);

	game->Run();

	delete game;
}
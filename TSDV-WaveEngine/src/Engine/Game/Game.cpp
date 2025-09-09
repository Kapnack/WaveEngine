#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"

Game::Game(int width, int height) : Engine(width, height)
{
	Init();
}

Game::~Game()
{
}

void Game::Init()
{
	Vector3 pos;
	shape = new Square(GetRenderer(), pos);
	shape2 = new Triangle(GetRenderer(), pos);
}

void Game::Update()
{
	if (shape)
		shape->Draw();

	if (shape2)
		shape2->Draw();
}

void Game::Unload()
{
	delete shape;
	delete shape2;
}

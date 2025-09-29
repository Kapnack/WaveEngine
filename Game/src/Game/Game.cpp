#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"

Game::Game(int width, int height) : Engine(width, height)
{
	Init();
}

Game::~Game()
{
	Unload();
}

void Game::Init()
{
	shape = new Square(GetRenderer());
	shape2 = new Triangle(GetRenderer());

	shape->SetPosition(pos);

	pos = Vector3(width / 2, height / 2, 0);

	shape2->SetPosition(pos);

	pos = Vector3(width / 2, height / 2, 0);
	shape2->SetScale(pos);
}

void Game::Update()
{
	float delta = GetDeltaTime();

	float rotate = 45.0f;

	shape2->Rotate(rotate * GetDeltaTime());

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

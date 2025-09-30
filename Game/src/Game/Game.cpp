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
	shape = new Square(GetRenderer(), Vector4(0, 0, 255, 1));
	shape2 = new Triangle(GetRenderer(), Vector4(255, 155, 0, 1));

	squarePos = Vector3(100, height - 100.0f, 0);
	trianglePos = Vector3(width - 200.0f, height / 2, 0);

	shape->SetPosition(squarePos);
	shape2->SetPosition(trianglePos);

	Vector3 scale = Vector3(75, 75, 0);

	shape->SetScale(scale);
	shape2->SetScale(scale);
}

void Game::Update()
{
	float delta = GetDeltaTime();

	float rotate = -90.0f;

	shape->Rotate(rotate * delta);

	//Square movement
	if (shape->position.x <= width - 100.0f && shape->position.y <= 100) //Derecha abajo
	{
		shape->Translate(500 * delta, 0);
	}
	else if (shape->position.x <= 100.0f && shape->position.y >= 100) //Baja izquierda
	{ 
		shape->Translate(0, -500 * delta);
	}
	else if (shape->position.x >= width - 100.0f && shape->position.y <= height - 100.0f) //Sube derecha
	{
		shape->Translate(0, 500 * delta);
	}
	else if (shape->position.x >= 100.0f && shape->position.y >= height - 100.0f) //Izquierda arriba
	{
		shape->Translate(-500 * delta, 0);
	}

	//Triangle movement
	if (shape2->position.y <= height - 100.0f && isGoingUp == true)
	{
		shape2->Translate(0, 250 * delta);

		shape2->SetRotation(0.0f);

		if (shape2->position.y >= height - 100.0f)
		{
			isGoingUp = false;
			isGoingDown = true;
		}		
	}
	else if (shape2->position.y >= 100.0f && isGoingDown == true)
	{
		shape2->Translate(0, -250 * delta);

		shape2->SetRotation(180.0f);

		if (shape2->position.y <= 100.0f)
		{
			isGoingUp = true;
			isGoingDown = false;
		}
	}

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

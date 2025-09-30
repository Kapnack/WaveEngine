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
	pinkSquare = new Square(GetRenderer(), Vector4(1.0f, 0.5f, 0.8f, 1.0f));
	blueSquare = new Square(GetRenderer(), Vector4(0.0f, 0.0f, 1.0f, 1.0f));

	pos = Vector3(width / 2, height / 2, 0);
	pinkSquare->SetPosition(pos);

	originalScale = Vector3(width / 10, width / 10, 0);
	pinkSquare->SetScale(originalScale);

	//----------------------------------------------------------------------

	pos = Vector3(width / 8, height - height / 8, 0);

	blueSquare->SetPosition(pos);

	pos = Vector3(width / 10, width / 10, 0);
	blueSquare->SetScale(pos);
}

void Game::Update()
{
	float delta = GetDeltaTime();

	blueSquare->Rotate(-45.0f * GetDeltaTime());

	bool isOnTopLeft = blueSquare->GetPosition().x > width - width / 10;
	bool isOnTopRight = blueSquare->GetPosition().x < width / 10;
	bool isOnButtonLeft = blueSquare->GetPosition().y < height / 10;
	bool isOnButtonRight = blueSquare->GetPosition().y > height - height / 10;

	float speedSquare = 400;

	if (!reverseMovement)
	{
		if (!isOnTopLeft)
		{
			blueSquare->Translate(Vector3(speedSquare * delta, 0, 0));
		}
		else
		{
			if (!isOnButtonLeft)
				blueSquare->Translate(Vector3(0, -speedSquare * delta, 0));
			else
				reverseMovement = true;
		}
	}
	else
	{
		if (!isOnTopRight)
		{
			blueSquare->Translate(Vector3(-speedSquare * delta, 0, 0));
		}
		else
		{
			if (!isOnButtonRight)
				blueSquare->Translate(Vector3(0, speedSquare * delta, 0));
			else
				reverseMovement = false;
		}
	};

	if (pinkSquare->GetScale() > originalScale)
		pinkSquare->Scale(Vector3(1 * delta, 1 * delta, 0));

	if (pinkSquare)
		pinkSquare->Draw();

	if (blueSquare)
		blueSquare->Draw();
}

void Game::Unload()
{
	delete pinkSquare;
	delete blueSquare;
}

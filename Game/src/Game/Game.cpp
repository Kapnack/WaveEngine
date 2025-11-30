#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "TextureImporter/TextureImporter.h"
#include "CollisionManager/CollisionManager.h"
#include "Input/Input.h"

Game::Game(int width, int height) : BaseGame(width, height)
{
	Init();
}

Game::~Game()
{
	Unload();
}

void Game::Init()
{
	blueSquare = new Square(GetRenderer());
	pinkSquare = new Square(GetRenderer());
	triangle = new Triangle(GetRenderer(), Vector4(1, 0.6f, 0, 1));

	for (int i = 0; i < starParts; i++)
		star[i] = new Triangle(GetRenderer(), Vector4(1, 0, 0, 1));

	//Pos sets
	pos = Vector3(width / 2, height / 2, 0);
	pinkSquare->SetPosition(pos);
	triangle->SetPosition(Vector3(width - 200, height / 2, 0));

	for (int i = 0; i < starParts; i++)
	{
		star[i]->SetPosition(Vector3(200, 200, 0));

		if (i == starParts - 1)
			star[i]->SetPosition(Vector3(200, 200 - star[i]->GetScale().y * 20, 0));
	}

	//Scale Set
	scale = Vector3(width / 2, width / 2, 0);
	blueSquare->SetScale(scale * 0.2f);
	pinkSquare->SetScale(scale * 0.4f);
	triangle->SetScale(scale * 0.2f);

	for (int i = 0; i < starParts; i++)
		star[i]->SetScale(scale * 0.2f);

	//Extras
	star[1]->SetRotation(180);

	startingScale = pinkSquare->GetScale();
	endScale = pinkSquare->GetScale() * 1.5f;

	blueSquare->SetColor(Vector4(0, 0, 1, 1));
	pinkSquare->SetColor(Vector4(1, 0.7, 0.7, 1));
}

void Game::Update()
{
	float delta = GetDeltaTime();

	if (shouldScale)
	{
		pinkSquare->Scale(Vector3(100 * delta, 100 * delta, 0));
		shouldScale = pinkSquare->GetScale().y < endScale.y;
	}
	else
	{
		pinkSquare->Scale(Vector3(-100 * delta, -100 * delta, 0));
		shouldScale = pinkSquare->GetScale().y < startingScale.y;
	}

	blueSquare->Rotate(rotate * delta);

	//Square movement
	if (blueSquare->GetPos().x <= width - 100.0f && blueSquare->GetPos().y <= 100) //Derecha abajo
		blueSquare->Translate(500 * delta, 0);
	else if (blueSquare->GetPos().x <= 100.0f && blueSquare->GetPos().y >= 100) //Baja izquierda
		blueSquare->Translate(0, -500 * delta);
	else if (blueSquare->GetPos().x >= width - 100.0f && blueSquare->GetPos().y <= height - 100.0f) //Sube derecha
		blueSquare->Translate(0, 500 * delta);
	else if (blueSquare->GetPos().x >= 100.0f && blueSquare->GetPos().y >= height - 100.0f) //Izquierda arriba
		blueSquare->Translate(-500 * delta, 0);

	//Triangle movement
	if (triangle->GetPos().y <= height - 100.0f && isGoingUp == true)
	{
		triangle->Translate(0, 250 * delta);
		triangle->SetRotation(0.0f);

		if (triangle->GetPos().y >= height - 100.0f)
		{
			isGoingUp = false;
			isGoingDown = true;
		}
	}
	else if (triangle->GetPos().y >= 100.0f && isGoingDown == true)
	{
		triangle->Translate(0, -250 * delta);

		triangle->SetRotation(180.0f);

		if (triangle->GetPos().y <= 100.0f)
		{
			isGoingUp = true;
			isGoingDown = false;
		}
	}

	//Estrella
	star[0]->Rotate(rotate * delta);
	star[1]->Rotate(-rotate * delta);

	if (blueSquare)
		blueSquare->Draw();

	if (pinkSquare)
		pinkSquare->Draw();

	if (triangle)
		triangle->Draw();

	for (int i = 0; i < starParts; i++)
		if (star[i])
			star[i]->Draw();
}

void Game::Unload()
{
	delete blueSquare;
	delete pinkSquare;
	delete triangle;

	for (int i = 0; i < starParts; i++)
		delete star[i];
}

#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "TextureImporter/TextureImporter.h"

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

	TextureImporter textureImporter;

	textureImporter.LoadTexture("C:/Users/Kapnack/Desktop/WaveEngine/Game/Sprites/graficosImage.png");

	sprite = new Sprite(textureImporter.GetLoadedTexture(), Vector4(0, 1, 0, 1), GetRenderer());

	pos = Vector3(width / 2, height / 2, 0);

	sprite->SetPosition(pos);

	pos = Vector3(width / 2, height / 2, 0);
	sprite->SetScale(pos);
}

void Game::Update()
{
	float delta = GetDeltaTime();

	float rotate = 45.0f;

	shape2->Rotate(rotate * GetDeltaTime());

	// if (shape)
	// 	shape->Draw();

	timer += GetDeltaTime();

	if (timer > 3)
		sprite->SetColor(Vector4(1, 1, 1, 1));

	sprite->Translate(Vector3(0, 10 * GetDeltaTime(), 0));

	if (sprite)
		sprite->Draw();

	// if (shape2)
	// 	shape2->Draw();
}

void Game::Unload()
{
	delete shape;
	delete shape2;
	delete sprite;
}

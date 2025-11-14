#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "Entity/Entity2D//Animation/Animation.h"
#include "TextureImporter/TextureImporter.h"
#include "Input/Input.h"

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
	TextureImporter textureImporter;

	textureImporter.LoadTexture("Sprites/test.jpg");

	sprite = new Sprite(textureImporter.GetLoadedTexture(), GetRenderer());

	pos = Vector3(width / 2, height / 2, 0);

	sprite->SetPosition(pos);

	pos = Vector3(width / 2, height / 2, 0);
	sprite->SetScale(pos);

	sprite->SetColor(Vector4(1, 0, 0, 1));

	animation = new Animation(Vector2(75, 30), Vector2(175, 230), Vector2(1024, 300), 5, 0.0001);
}

void Game::Update()
{
	float delta = GetDeltaTime();

	float rotate = 45.0f;

	timer += GetDeltaTime();

	if (sprite)
		sprite->Draw();
}

void Game::Unload()
{
	delete sprite;
	delete animation;
}

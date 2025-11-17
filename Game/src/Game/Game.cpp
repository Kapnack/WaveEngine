#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "Entity/Entity2D//Animation/Animation.h"
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
	TextureImporter textureImporter;
	TextureImporter texture2;

	textureImporter.LoadTexture("Sprites/Pokemon.png");
	character = new Sprite(textureImporter.GetLoadedTexture(), GetRenderer());

	texture2.LoadTexture("Sprites/graficosImage.png");
	obstacle = new Sprite(texture2.GetLoadedTexture(), GetRenderer());

	pos = Vector3(width / 2, height / 2, 0);

	character->SetPosition(pos);

	obstacle->SetPosition(Vector3(character->GetPos().x - width / 4, height / 2, 0));

	pos = Vector3(width / 2, height / 2, 0);
	character->SetScale(pos);
	obstacle->SetScale(pos);

	character->SetColor(Vector4(1, 1, 1, 1));
	obstacle->SetColor(Vector4(1, 1, 1, 1));

	WalkDown = new Animation(Vector2(0, 0), Vector2(64, 64), Vector2(256, 256), 4, 1);
	WalkUp = new Animation(Vector2(0, 64), Vector2(64, 64), Vector2(256, 256), 4, 1);
	WalkRight = new Animation(Vector2(0, 128), Vector2(64, 64), Vector2(256, 256), 4, 1);
	WalkLeft = new Animation(Vector2(0, 192), Vector2(64, 64), Vector2(256, 256), 4, 1);

	character->SetAnimation(WalkDown);
}

const float movementSpeed = 150;

void Game::Update()
{
	float delta = GetDeltaTime();

	float rotate = 45.0f;

	timer += GetDeltaTime();

	bool colliding = CollisionManager::CheckCollision(character, obstacle);

	if (colliding)
	{
		character->GoToPreviousPos();

		if (Input::IsKeyPressed(Keys::E))
		{
			obstacle->Translate(Vector3::Right() * movementSpeed * delta);
		}
	}

	else if (Input::IsKeyPressed(Keys::S) && !colliding)
	{
		character->SetAnimation(WalkDown);
		character->Update();
		character->Translate(movementSpeed * Vector3::Down() * delta);
	}
	else if (Input::IsKeyPressed(Keys::W) && !colliding)
	{
		character->SetAnimation(WalkUp);
		character->Update();
		character->Translate(movementSpeed * Vector3::Up() * delta);
	}
	else if (Input::IsKeyPressed(Keys::A) && !colliding)
	{
		character->SetAnimation(WalkLeft);
		character->Update();
		character->Translate(movementSpeed * Vector3::Right() * delta);
	}
	else if (Input::IsKeyPressed(Keys::D) && !colliding)
	{
		character->SetAnimation(WalkRight);
		character->Update();
		character->Translate(movementSpeed * Vector3::Left() * delta);
	}

	if (character)
		character->Draw();

	if (obstacle)
		obstacle->Draw();
}

void Game::Unload()
{
	delete character;
	delete obstacle;
	delete WalkDown;
	delete WalkUp;
	delete WalkLeft;
	delete WalkRight;
}

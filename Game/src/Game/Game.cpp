#include "Game.h"

#include "TextureImporter/TextureImporter.h"
#include "CollisionManager/CollisionManager.h"
#include "Material/MaterialManager.h"
#include "Input/Input.h"
#include "Vector2.h"
#include "TileMap/TileMap.h"
#include <string>

Game::Game(int width, int height) : BaseGame(width, height)
{
	Init(width, height);
}

Game::~Game()
{
	Unload();
}

void Game::Init(const int& width, const int& height)
{
	CreateCollisionManager();

	player = GetEntityFactory()->Create<Sprite>();

	const string json = "Sprites/map.json";
	const string spriteSheet = "Sprites/spritesheet.png";

	tileMap = GetEntityFactory()->CreateTileMap(json, true, spriteSheet, true);

	unsigned int samusTexture = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/battlecity_general.png");


	GetEntityManager();

	GetEntityManager()->Get<Sprite>(player)->SetTexture(samusTexture);
	GetEntityManager()->Get(player)->SetScale(Vector2(32, 32));

	Vector2 frameArea = Vector2(16, 15);
	Vector2 textureSize = Vector2(400, 256);
	float timeAnimation = 0.5f;
	int amountOfFrames = 2;

	walkingUp = new Animation(Vector2(0, textureSize.y), frameArea, textureSize, amountOfFrames, timeAnimation);
	walkingLeft = new Animation(Vector2(33, textureSize.y), frameArea, textureSize, amountOfFrames, timeAnimation);
	walkingDown = new Animation(Vector2(64, textureSize.y), frameArea, textureSize, amountOfFrames, timeAnimation);
	walkingRight = new Animation(Vector2(96, textureSize.y), frameArea, textureSize, amountOfFrames, timeAnimation);

	GetEntityManager()->Get<Sprite>(player)->SetAnimation(walkingLeft);
	GetEntityManager()->Get<Sprite>(player)->SetLayer(-3);
}

void Game::Update()
{
	if (!GetEntityManager()->TryGet(player))
		return;

	if (GetInput()->IsKeyPressed(Keys::W))
	{
		GetEntityManager()->Get<Sprite>(player)->SetAnimation(walkingUp);
		GetEntityManager()->Get(player)->Translate(Vector2::Up() * playerVelocity * GetDeltaTime());
	}
	else if (GetInput()->IsKeyPressed(Keys::A))
	{
		GetEntityManager()->Get<Sprite>(player)->SetAnimation(walkingLeft);
		GetEntityManager()->Get(player)->Translate(Vector2::Left() * playerVelocity * GetDeltaTime());
	}
	else if (GetInput()->IsKeyPressed(Keys::S))
	{
		GetEntityManager()->Get<Sprite>(player)->SetAnimation(walkingDown);
		GetEntityManager()->Get(player)->Translate(Vector2::Down() * playerVelocity * GetDeltaTime());
	}
	else if (GetInput()->IsKeyPressed(Keys::D))
	{
		GetEntityManager()->Get<Sprite>(player)->SetAnimation(walkingRight);
		GetEntityManager()->Get(player)->Translate(Vector2::Right() * playerVelocity * GetDeltaTime());
	}

	GetEntityManager()->Get<Sprite>(player)->Update();

	if (GetEntityManager()->TryGet<TileMap>(tileMap))
		if (GetCollsionManager()->CheckCollision(player, *GetEntityManager()->Get<TileMap>(tileMap)))
			GetEntityManager()->Get(player)->GoToPreviousPos();

}

void Game::Draw()
{
}

void Game::Unload()
{
	delete walkingLeft;
	delete walkingUp;
	delete walkingDown;
	delete walkingRight;
}

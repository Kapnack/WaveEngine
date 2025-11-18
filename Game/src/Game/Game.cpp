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

	textureImporter.LoadTexture("Sprites/Knuckles_Sprite_Sheet.png");
	knuckles = new Sprite(textureImporter.GetLoadedTexture(), GetRenderer());

	texture2.LoadTexture("Sprites/Rock.jfif");
	obstacle = new Sprite(texture2.GetLoadedTexture(), GetRenderer());

	pos = Vector3(width / 2, height / 2, 0);

	knuckles->SetPosition(pos);

	obstacle->SetPosition(Vector3(knuckles->GetPos().x + width / 4, height / 2, 0));

	pos = Vector3(width / 2, height / 2, 0);
	knuckles->SetScale(pos * 0.5f);
	obstacle->SetScale(pos * 0.5f);

	knuckles->SetColor(Vector4(1, 1, 1, 1));
	obstacle->SetColor(Vector4(1, 1, 1, 1));

	Vector2 knuclesSpriteArea = Vector2(35, 40);
	Vector2 knuclesTextureSize = Vector2(646, 473);
	float animationTime = 1.0f;

	idle = new Animation(Vector2(0, 0), knuclesSpriteArea, knuclesTextureSize, 1, animationTime);
	WalkRight = new Animation(Vector2(0, knuclesTextureSize.y - 44), Vector2(34, knuclesSpriteArea.y), knuclesTextureSize, 5, animationTime);
	WalkDown = new Animation(Vector2(1, knuclesTextureSize.y - 127), Vector2(32, knuclesSpriteArea.y), knuclesTextureSize, 5, animationTime);
	WalkUp = new Animation(Vector2(0, 64), knuclesSpriteArea, knuclesTextureSize, 4, animationTime);
	onRock = new Animation(Vector2(424, knuclesTextureSize.y - 95), knuclesSpriteArea, knuclesTextureSize, 4, animationTime);

	knuckles->SetAnimation(idle);

	rockAnim = new Animation(Vector2(72, 207 - 18), Vector2(91, 60), Vector2(244, 207), 1, animationTime);
	obstacle->SetAnimation(rockAnim);

}


void Game::Update()
{
	const float movementSpeed = 300;
	float delta = GetDeltaTime();

	float rotate = 45.0f;

	timer += GetDeltaTime();

	bool colliding = CollisionManager::CheckCollision(knuckles, obstacle);
	bool near = knuckles->GetCollider().x + knuckles->GetCollider().width + movementSpeed * 2 * delta > obstacle->GetCollider().x;

	if (colliding || near)
	{
		if (colliding)
			knuckles->GoToPreviousPos();

		knuckles->SetAnimation(onRock);

		if (Input::IsKeyPressed(Keys::E) && colliding)
		{
			obstacle->Translate(Vector3::Left() * movementSpeed * delta);
		}
	}

	if (Input::IsKeyPressed(Keys::S))
	{
		knuckles->SetAnimation(WalkDown);
	}
	else if (Input::IsKeyPressed(Keys::A) && !colliding)
	{
		if (!near)
			knuckles->SetAnimation(WalkRight);

		knuckles->Translate(movementSpeed * Vector3::Right() * delta);
	}
	else if (Input::IsKeyPressed(Keys::D) && !colliding)
	{
		if (!near)
			knuckles->SetAnimation(WalkRight);

		knuckles->Translate(movementSpeed * Vector3::Left() * delta);
	}
	else if (!colliding)
	{
		knuckles->SetAnimation(idle);
	}

	knuckles->Update();

	if (knuckles)
		knuckles->Draw();

	if (obstacle)
		obstacle->Draw();
}

void Game::Unload()
{
	delete knuckles;
	delete rockAnim;
	delete onRock;
	delete obstacle;
	delete WalkDown;
	delete idle;
	delete WalkUp;
	delete WalkLeft;
	delete WalkRight;
}

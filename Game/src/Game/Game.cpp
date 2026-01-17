#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "TextureImporter/TextureImporter.h"
#include "CollisionManager/CollisionManager.h"
#include "Material/MaterialManager.h"
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
	const string json = "Sprites/map.json";
	const string spriteSheet = "Sprites/spritesheet.png";

	tileMap = new TileMap(json, spriteSheet, Vector2{ 128, 160 });

	TextureImporter textureImporter;

	textureImporter.LoadTexture("Sprites/Samus Aran Sprite Sheet.png");

	sprite = new Sprite(textureImporter.GetLoadedTexture());
	sprite->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	sprite->SetPosition(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });

	otherThing = new Sprite(textureImporter.GetLoadedTexture());
	otherThing->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	otherThing->SetPosition(Vector3{ 0,0,0 });
}

void Game::Update()
{
	if (GetInput()->IsKeyPressed(Keys::W))
		sprite->Translate(Vector3::Up() * GetTime()->GetDeltaTime() * 100);

	if (GetInput()->IsKeyPressed(Keys::S))
		sprite->Translate(Vector3::Down() * GetTime()->GetDeltaTime() * 100);

	if (GetInput()->IsKeyPressed(Keys::A))
		sprite->Translate(Vector3::Left() * GetTime()->GetDeltaTime() * 100);

	if (GetInput()->IsKeyPressed(Keys::D))
		sprite->Translate(Vector3::Right() * GetTime()->GetDeltaTime() * 100);


	tileMap->Draw();

	sprite->Draw();
	otherThing->Draw();
}

void Game::Unload()
{
	delete tileMap;
	delete sprite;
	delete otherThing;
}

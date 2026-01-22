#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "TextureImporter/TextureImporter.h"
#include "CollisionManager/CollisionManager.h"
#include "Material/MaterialManager.h"
#include "Input/Input.h"

Game::Game(int width, int height) : BaseGame(width, height)
{
	Init(width, height);
}

Game::~Game()
{
}

void Game::Init(int width, int height)
{
	BaseGame::Init(width, height);

	/*
	sprite = new Sprite();
	sprite->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	sprite->SetPosition(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });

	otherThing = new Sprite(textureImporter.GetLoadedTexture());
	otherThing->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	otherThing->SetPosition(Vector3{ 0,0,0 });*/

	const string json = "Sprites/map.json";
	const string spriteSheet = "Sprites/spritesheet.png";

	tileMap = new TileMap(json, spriteSheet, Vector2{ 128, 160 });

	TextureImporter textureImporter;

	textureImporter.LoadTexture("Sprites/Samus Aran Sprite Sheet.png");

	Vector2 textureSize = Vector2(860, 762);

	GetEntityManager();

	EntityFactory* factory = GetEntityFactory();

	entityController = new EntityController(factory->Create<Sprite>());

	GetEntityManager()->Get<Sprite>(entityController->GetEntityID())->SetTexture(textureImporter.GetLoadedTexture());
	GetEntityManager()->Get<Sprite>(entityController->GetEntityID())->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	GetEntityManager()->Get<Sprite>(entityController->GetEntityID())->SetPosition(Vector3{ 100,100,0 });
}

void Game::Update()
{
	entityController->Update(GetDeltaTime());
}

void Game::Draw()
{
}

void Game::Unload()
{
	delete entityController;
	delete tileMap;
}

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

	EntityFactory* factory = GetEntityFactory();

	unsigned int player = factory->Create<Sprite>();
	unsigned int player2 = factory->Create<Sprite>();

	const string json = "Sprites/map.json";
	const string spriteSheet = "Sprites/spritesheet.png";

	tileMap = new TileMap(json, spriteSheet);

	unsigned int samusTexture = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/Samus Aran Sprite Sheet.png");

	Vector2 textureSize = Vector2(860, 762);

	GetEntityManager();

	entityController = new EntityController();

	GetEntityManager()->Get<Sprite>(player)->SetTexture(samusTexture);
	GetEntityManager()->Get<Sprite>(player)->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	GetEntityManager()->Get<Sprite>(player)->SetPosition(Vector3{ 100,100,0 });

	entityController->AddEntityID(1);

	GetEntityManager()->Get<Sprite>(player2)->SetTexture(samusTexture);
	GetEntityManager()->Get<Sprite>(player2)->SetColor(Vector4{ 1,0,0,1 });
	GetEntityManager()->Get<Sprite>(player2)->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	GetEntityManager()->Get<Sprite>(player2)->SetPosition(Vector3{ (float)GetWindow()->GetWidth() / 2 - 100, (float)GetWindow()->GetHeight() / 2 - 100,0 });
}

void Game::Update()
{
	entityController->Update(GetDeltaTime());

	if (GetInput()->IsKeyPressed(Keys::Q))
		GetMaterialManager()->DeleteMaterial(GetEntityManager()->Get<Entity>(2)->GetMaterial());
}

void Game::Draw()
{
	tileMap->Draw();
}

void Game::Unload()
{
	delete entityController;
	delete tileMap;
}

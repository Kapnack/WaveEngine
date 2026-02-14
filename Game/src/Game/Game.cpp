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
}

void Game::Init(int width, int height)
{
	BaseGame::Init(width, height);
	CreateCollisionManager();

	unsigned int player = GetEntityFactory()->Create<Sprite>();
	unsigned int player2 = GetEntityFactory()->Create<Sprite>();

	const string json = "Sprites/map.json";
	const string spriteSheet = "Sprites/spritesheet.png";

	tileMap = new TileMap(json, spriteSheet);

	unsigned int samusTexture = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/Samus Aran Sprite Sheet.png");

	Vector2 textureSize = Vector2(860, 762);

	GetEntityManager();

	GetEntityManager()->Get<Sprite>(player)->SetTexture(samusTexture);
	GetEntityManager()->Get<Sprite>(player)->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	GetEntityManager()->Get<Sprite>(player)->SetPosition(Vector3{ 100,100,0 });

	GetEntityManager()->Get<Sprite>(player2)->SetTexture(samusTexture);
	GetEntityManager()->Get<Sprite>(player2)->SetColor(Vector4{ 1,0,0,1 });
	GetEntityManager()->Get<Sprite>(player2)->SetScale(Vector3{ (float)GetWindow()->GetWidth() / 2, (float)GetWindow()->GetHeight() / 2, 0 });
	GetEntityManager()->Get<Sprite>(player2)->SetPosition(Vector3{ (float)GetWindow()->GetWidth() / 2 - 100, (float)GetWindow()->GetHeight() / 2 - 100,0 });
}

void Game::Update()
{
	if (GetInput()->IsKeyPressed(Keys::Q))
		GetMaterialManager()->DeleteMaterial(GetEntityManager()->Get<Entity>(2)->GetMaterial());

	Entity2D* entity = GetEntityManager()->Get<Entity2D>(1);

	if (GetCollsionManager()->CheckCollision(entity, *tileMap))
		cout << "IT WORKS!!!";
}

void Game::Draw()
{
}

void Game::Unload()
{
	delete tileMap;
}

#include "TileMap.h"

#include "ServiceProvider/ServiceProvider.h"
#include "TextureImporter/TextureImporter.h"
#include "FileReader/FileReader.h"
#include "TextureImporter/Texture.h"
#include "Entity/EntityFactory.h"
#include "Entity/EntityManager.h"
#include "Window/Window.h"

#include <iostream>

TileMap::TileMap( const string_view mapFilePath, const bool& mapFileAddAbsolutePath, const string_view texturePath, const bool& texturePathAddAbsolutePath, const unsigned int& ID) : Entity2D(ID)
{
	texture = texturePathAddAbsolutePath ? ServiceProvider::Instance().Get<TextureImporter>()->LoadTextureAbsolutePath(texturePath)
		: ServiceProvider::Instance().Get<TextureImporter>()->LoadTexture(texturePath);

	if (!ServiceProvider::Instance().Get<TextureManager>()->GetTexture(texture))
		return;

	this->textureSize = ServiceProvider::Instance().Get<TextureManager>()->GetTexture(texture)->GetRes();
}

TileMap::~TileMap()
{
	for (int layer = 0; layer < layersAmount; ++layer)
	{
		for (int y = 0; y < columnsAmount; ++y)
		{
			for (int x = 0; x < rowAmount; ++x)
				GetEntityManager()->DeleteEntity(_tileMapGrid[layer][y][x]);

			delete[] _tileMapGrid[layer][y];
		}

		delete[] _tileMapGrid[layer];
	}

	delete[] _tileMapGrid;
}

Window* TileMap::GetWindow() const
{
	return ServiceProvider::Instance().Get<Window>();
}

EntityManager* TileMap::GetEntityManager() const
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

Tile* TileMap::GetTile(const unsigned int id) const
{
	for (vector<unsigned int>::iterator it = GetEntityManager()->GetAllOfType<Tile>().begin(); it != GetEntityManager()->GetAllOfType<Tile>().end(); ++it)
	{
		Tile* tile = GetEntityManager()->Get<Tile>(*it);

		if (tile->GetTileID() == id)
			return tile;
	}

	return nullptr;
}

void TileMap::SetTileDimensions(float tileWidth, float tileHeigth) noexcept
{
	_worldTileWidth = tileWidth;
	_worldTileHeight = tileHeigth;
}

void TileMap::SetTexture(unsigned int texture) noexcept
{
	this->texture = texture;
}

void TileMap::ImportTileMap(const string_view filePath, const bool& addAbsolutePath)
{
	const string TileSizeName = "tileSize";
	const string MapWidthName = "mapWidth";
	const string MapHeightName = "mapHeight";
	const string LayersName = "layers";
	const string IdName = "id";
	const string ColName = "x";
	const string RowName = "y";
	const string tileName = "tiles";
	const string colliderName = "collider";

	const string jsonString = addAbsolutePath ? ServiceProvider::Instance().Get<FileReader>()->ReadFileAbsolutePath(filePath)
		: ServiceProvider::Instance().Get<FileReader>()->ReadFile(filePath);

	if (jsonString == "")
		return;

	data = json::parse(jsonString);

	if (data == "")
		return;

	rowAmount = data[MapWidthName];
	columnsAmount = data[MapHeightName];

	float tileSize = data[TileSizeName];
	_tilePixelSize = tileSize;

	layersAmount = data[LayersName].size();
	_tileMapGrid = new unsigned int** [layersAmount](nullptr);

	unsigned int id = 0;

	for (int layer = 0; layer < layersAmount; ++layer)
	{
		bool layerHasCollision = data[LayersName][layer][colliderName];

		_tileMapGrid[layer] = new unsigned int* [columnsAmount](0);

		for (int row = 0; row < columnsAmount; ++row)
		{
			_tileMapGrid[layer][row] = new unsigned int[rowAmount]();
		}

		// FILL ONLY DEFINED TILES FROM JSON
		const basic_json<>::value_type tilesJson = data[LayersName][layer][tileName];
		for (const basic_json<>::value_type& tileJson : tilesJson)
		{
			unsigned int spriteSheetID = stoi(tileJson[IdName].get<string>());
			unsigned int col = tileJson[ColName];
			unsigned int row = tileJson[RowName];

			unsigned int newTile = ServiceProvider::Instance().Get<EntityFactory>()->Create<Tile>();

			Tile* tile = ServiceProvider::Instance().Get<EntityManager>()->Get<Tile>(newTile);

			tile->SetTexture(texture);

			tile->SetSpriteSheetID(spriteSheetID);
			tile->SetTileID(id);
			tile->SetLayer(-1.0f - layer);

			tile->SetCollide(layerHasCollision);

			SetTileUV(*tile, spriteSheetID);

			_tileMapGrid[layer][row][col] = newTile;

			++id;
		}
	}

	UpdateTilesPositions();
}

void TileMap::UpdateTilesPositions()
{
	Window* window = GetWindow();
	if (!window) return;

	const float windowWidth = window->GetWidth();
	const float windowHeight = window->GetHeight();

	_worldTileWidth = windowWidth / rowAmount;
	_worldTileHeight = windowHeight / columnsAmount;

	Tile* tile;

	for (unsigned int layer = 0; layer < layersAmount; ++layer)
	{
		for (unsigned int row = 0; row < columnsAmount; ++row)
		{
			for (unsigned int col = 0; col < rowAmount; ++col)
			{
				tile = ServiceProvider::Instance().Get<EntityManager>()->TryGet<Tile>(_tileMapGrid[layer][row][col]);

				if (!tile)
					continue;

				tile->SetScale({ _worldTileWidth, _worldTileHeight, 1 });

				float posX = (_worldTileWidth * 0.5f) + (_worldTileWidth * col);
				float posY = windowHeight - (_worldTileHeight * 0.5f) - (_worldTileHeight * row);

				tile->SetPosition({ posX, posY, 0 });
			}
		}
	}
}

void TileMap::SetTileUV(Tile& tile, unsigned int id) const
{
	const string TileSizeName = "tileSize";
	float tileSize = data[TileSizeName];

	float texW = textureSize.x;
	float texH = textureSize.y;

	unsigned int cols = static_cast<unsigned int>(texW / tileSize);

	unsigned int row = id / cols;
	unsigned int col = id % cols;

	const float halfU = 0.5f / texW;
	const float halfV = 0.5f / texH;

	float u0 = (col * tileSize) / texW + halfU;
	float u1 = ((col + 1) * tileSize) / texW - halfU;

	float v0 = 1.0f - ((row + 1) * tileSize) / texH + halfV;
	float v1 = 1.0f - (row * tileSize) / texH - halfV;

	tile.SetUVCordinates({ u0, v1 }, { u1, v0 });
}

float TileMap::GetMapWidth() const
{
	return rowAmount;
}

float TileMap::GetMapHeight() const
{
	return columnsAmount;
}

float TileMap::GetTileWidth() const
{
	return _worldTileWidth;
}

float TileMap::GetTileHeight() const
{
	return _worldTileHeight;
}

int TileMap::GetLayerCount() const
{
	return layersAmount;
}

unsigned int TileMap::GetTileAt(const int& layer, const int& row, const int& col) const
{
	if (layer < 0 || layer >= layersAmount)
		return Entity::NULL_ENTITY;

	if (row < 0 || row >= columnsAmount)
		return Entity::NULL_ENTITY;

	if (col < 0 || col >= rowAmount)
		return Entity::NULL_ENTITY;

	return _tileMapGrid[layer][row][col];
}

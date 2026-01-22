#include "TileMap.h"

#include "FileReader/FileReader.h"
#include "TextureImporter/TextureImporter.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Window/Window.h"

#include <iostream>

TileMap::TileMap(const string& mapFilePath, const string& texturePath, const Vector2& textureSize)
{
	TextureImporter textureImporter;
	textureImporter.LoadTexture(texturePath);
	texture = textureImporter.GetLoadedTexture();

	this->textureSize = textureSize;

	ImportTileMap(mapFilePath);
}

TileMap::~TileMap()
{
	for (int layer = 0; layer < layersAmount; ++layer)
	{
		for (int y = 0; y < columnsAmount; ++y)
		{
			for (int x = 0; x < rowAmount; ++x)
				delete _tileMapGrid[layer][y][x];

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

Tile* TileMap::GetTile(const unsigned int id) const
{
	for (int layer = 0; layer < layersAmount; ++layer)
		for (int y = 0; y < rowAmount; ++y)
			for (int x = 0; x < columnsAmount; ++x)
				if (_tileMapGrid[layer][y][x]->GetID() == id)
					return _tileMapGrid[layer][y][x];

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

void TileMap::ImportTileMap(const string& filePath)
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

	FileReader fileReader;

	const string jsonString = fileReader.ReadFile(filePath);

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
	_tileMapGrid = new Tile * **[layersAmount](nullptr);

	unsigned int id = 0;

	for (size_t layer = 0; layer < layersAmount; ++layer)
	{
		bool layerHasCollision = data[LayersName][layer][colliderName];

		_tileMapGrid[layer] = new Tile * *[columnsAmount](nullptr);

		for (size_t row = 0; row < columnsAmount; ++row)
		{
			_tileMapGrid[layer][row] = new Tile * [rowAmount](nullptr);
		}

		// FILL ONLY DEFINED TILES FROM JSON
		const auto& tilesJson = data[LayersName][layer][tileName];
		for (const auto& tileJson : tilesJson)
		{
			unsigned int spriteSheetID = stoi(tileJson[IdName].get<string>());
			unsigned int col = tileJson[ColName];
			unsigned int row = tileJson[RowName];

			Tile* tile = new Tile();

			tile->SetTexture(texture);

			tile->SetSpriteSheetID(spriteSheetID);
			tile->SetID(id);

			tile->SetCollide(layerHasCollision);

			SetTileUV(*tile, spriteSheetID);

			_tileMapGrid[layer][row][col] = tile;

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

	for (unsigned int layer = 0; layer < layersAmount; ++layer)
	{
		for (unsigned int row = 0; row < columnsAmount; ++row)
		{
			for (unsigned int col = 0; col < rowAmount; ++col)
			{
				Tile* tile = _tileMapGrid[layer][row][col];
				if (!tile) continue;

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

void TileMap::Draw()
{
	Window* window = GetWindow();
	if (!window) return;

	for (int layer = layersAmount - 1; layer >= 0; --layer)
	{
		for (unsigned int row = 0; row < columnsAmount; ++row)
		{
			for (unsigned int col = 0; col < rowAmount; ++col)
			{
				Tile* tile = _tileMapGrid[layer][row][col];

				if (tile == nullptr)
					continue;

				tile->Draw();
			}
		}
	}
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

Tile* TileMap::GetTileAt(const int& layer, const int& row, const int& col) const
{
	if (layer < 0 || layer >= layersAmount)
		return nullptr;

	if (row < 0 || row >= columnsAmount) // Y / height
		return nullptr;

	if (col < 0 || col >= rowAmount)     // X / width
		return nullptr;

	return _tileMapGrid[layer][row][col];
}

#pragma once

#include "Export.h"
#include "Tile.h"

#include "Window/Window.h"

#include <vector>
#include <string>

#include <../lib/json.hpp>

using namespace std;

using namespace nlohmann;

WAVEEXPORT class TileMap
{
public:

	WAVEEXPORT TileMap(const string& mapFilePath, const string& texturePath, const Vector2& textureSize);
	WAVEEXPORT ~TileMap();

	WAVEEXPORT void Draw();

	WAVEEXPORT float GetMapWidth();
	WAVEEXPORT float GetMapHeight();

	WAVEEXPORT float GetTileWidth();
	WAVEEXPORT float GetTileHeight();

	WAVEEXPORT int GetLayerCount();

	WAVEEXPORT Tile* GetTileAt(int layer, int col, int row);

private:

	vector<vector<vector<Tile*>>> _tileMapGrid;

	float _tileWidth;
	float _tileHeight;

	unsigned int texture;

	float _mapWidth;
	float _mapHeight;

	string _imagePath;

	json data;

	Vector2 tilesAmount;

	Vector2 textureSize;

	Tile* GetTile(unsigned int id);

	void SetTileDimensions(float tileWidth, float tileHeigth);

	void SetTexture(unsigned int texture);

	void ImportTileMap(const string& filePath);

	void SetTileUV(Tile& tile, unsigned int id);

	void UpdateTilesPositions();

	Window* GetWindow();
};

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

	WAVEEXPORT float GetMapWidth() const;
	WAVEEXPORT float GetMapHeight() const;

	WAVEEXPORT float GetTileWidth() const;
	WAVEEXPORT float GetTileHeight() const;

	WAVEEXPORT int GetLayerCount() const;

	WAVEEXPORT Tile* GetTileAt(const int& layer, const int& col, const int& row) const;

private:

	vector<vector<vector<Tile*>>> _tileMapGrid;

	const int EMPTY_TILE = -1;

	float _tileWidth;
	float _tileHeight;

	unsigned int texture;

	float _mapWidth;
	float _mapHeight;

	string _imagePath;

	json data;

	Vector2 tilesAmount;

	Vector2 textureSize;

	Tile* GetTile(const unsigned int id) const;

	void SetTileDimensions(float tileWidth, float tileHeigth) noexcept;

	void SetTexture(const unsigned int texture) noexcept;

	void ImportTileMap(const string& filePath);

	void SetTileUV(Tile& tile, unsigned int id) const;

	void UpdateTilesPositions();

	Window* GetWindow() const;
};

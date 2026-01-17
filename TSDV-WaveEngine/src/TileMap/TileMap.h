#pragma once

#include "Export.h"
#include "Tile.h"

#include "Window/Window.h"

#include <vector>
#include <string>


WAVEEXPORT class TileMap
{
public:

	WAVEEXPORT TileMap(const string& mapFilePath, const string& texturePath, const Vector2& textureSize);
	WAVEEXPORT ~TileMap();

	WAVEEXPORT void Draw();
private:

	vector<vector<vector<Tile*>>> _tileMapGrid;

	float _tileWidth;
	float _tileHeight;

	unsigned int texture;

	float _mapWidth;
	float _mapHeight;
	json data;
	Tile* GetTile(unsigned int id);

	void SetTileDimensions(float tileWidth, float tileHeigth);

	void SetTexture(unsigned int texture);

	void ImportTileMap(const string& filePath);

	void SetTileUV(Tile& tile, unsigned int id);

	void UpdateTilesPositions();

};

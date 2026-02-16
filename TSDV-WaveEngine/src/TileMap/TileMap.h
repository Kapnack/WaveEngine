#pragma once

#include "Entity/Entity2D/Entity2D.h"

#include "Export.h"
#include "Tile.h"

#include "Window/Window.h"
#include "Vector2.h"

#include <vector>
#include <string>

#include <../lib/json.hpp>

using namespace std;

using namespace nlohmann;

WAVEEXPORT class TileMap final : public Entity2D
{
public:

	WAVEEXPORT TileMap(const string& mapFilePath, const bool& mapFileAddAbsolutePath, const string& texturePath, const bool& texturePathAddAbsolutePath);
	WAVEEXPORT ~TileMap();

	WAVEEXPORT void Draw() override;

	WAVEEXPORT float GetMapWidth() const;
	WAVEEXPORT float GetMapHeight() const;

	WAVEEXPORT float GetTileWidth() const;
	WAVEEXPORT float GetTileHeight() const;

	WAVEEXPORT int GetLayerCount() const;

	WAVEEXPORT unsigned int GetTileAt(const int& layer, const int& col, const int& row) const;

private:

	unsigned int*** _tileMapGrid = nullptr;

	int layersAmount = 0;
	int rowAmount = 0;
	int columnsAmount = 0;

	float _tilePixelSize;
	float _worldTileWidth;
	float _worldTileHeight;

	unsigned int texture;

	string _imagePath;

	json data;

	Vector2 tilesAmount;

	Vector2 textureSize;

	Tile* GetTile(const unsigned int id) const;

	void SetTileDimensions(float tileWidth, float tileHeigth) noexcept;

	void SetTexture(const unsigned int texture) noexcept;

	void ImportTileMap(const string& filePath, const bool& addAbsolutePath);

	void SetTileUV(Tile& tile, unsigned int id) const;

	void UpdateTilesPositions();

	Window* GetWindow() const;

	EntityManager* GetEntityManager() const;
};

#include "TileMap.h"

#include "FileReader/FileReader.h"
#include "TextureImporter/TextureImporter.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Window/Window.h"

#include <iostream>

static constexpr int EMPTY_TILE = -1;

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
    for (int layer = 0; layer < _tileMapGrid.size(); ++layer)
        for (int y = 0; y < _tileMapGrid[layer].size(); ++y)
            for (int x = 0; x < _tileMapGrid[layer][y].size(); ++x)
                delete _tileMapGrid[layer][y][x];
}

Window* TileMap::GetWindow()
{
    return ServiceProvider::Instance().Get<Window>();
}

Tile* TileMap::GetTile(unsigned int id)
{
    for (auto& layer : _tileMapGrid)
        for (auto& row : layer)
            for (auto& tile : row)
                if (tile->GetID() == id)
                    return tile;

    return nullptr;
}

void TileMap::SetTileDimensions(float tileWidth, float tileHeigth)
{
    _tileWidth = tileWidth;
    _tileHeight = tileHeigth;
}

void TileMap::SetTexture(unsigned int texture)
{
    this->texture = texture;
}

void TileMap::ImportTileMap(const string& filePath)
{
}
void TileMap::UpdateTilesPositions()
{
}
void TileMap::Draw()
{
    Window* window = GetWindow();
    if (!window) return;

    for (int layer = _tileMapGrid.size() - 1; layer >= 0; --layer)
    {
        for (unsigned int row = 0; row < _mapHeight; ++row)
        {
            for (unsigned int col = 0; col < _mapWidth; ++col)
            {
                Tile* tile = _tileMapGrid[layer][row][col];

                if (tile->GetSpriteSheetID() == EMPTY_TILE)
                    continue;

                tile->Draw();
            }
        }
    }
}

float TileMap::GetMapWidth()
{
    return _mapWidth;
}

float TileMap::GetMapHeight()
{
    return _mapHeight;
}

float TileMap::GetTileWidth()
{
    return _tileWidth;
}

float TileMap::GetTileHeight()
{
    return _tileHeight;
}

int TileMap::GetLayerCount()
{
    return _tileMapGrid.size();
}

Tile* TileMap::GetTileAt(int layer, int col, int row)
{
    if (layer < 0 || layer >= (int)_tileMapGrid.size())
        return nullptr;

    if (row < 0 || row >= (int)_tileMapGrid[layer].size())
        return nullptr;

    if (col < 0 || col >= (int)_tileMapGrid[layer][row].size())
        return nullptr;

    return _tileMapGrid[layer][row][col];
}

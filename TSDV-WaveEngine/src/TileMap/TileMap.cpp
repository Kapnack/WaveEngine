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

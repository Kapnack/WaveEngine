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

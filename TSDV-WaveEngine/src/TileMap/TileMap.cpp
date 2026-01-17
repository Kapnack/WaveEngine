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
    data = json::parse(fileReader.ReadFile(filePath));

    _mapWidth = data[MapWidthName];
    _mapHeight = data[MapHeightName];

    float tileSize = data[TileSizeName];
    _tileWidth = tileSize;
    _tileHeight = tileSize;

    const size_t layersAmount = data[LayersName].size();
    _tileMapGrid.resize(layersAmount);

    unsigned int id = 0;

    for (size_t layer = 0; layer < layersAmount; ++layer)
    {
        bool layerHasCollision = data[LayersName][layer][colliderName];

        _tileMapGrid[layer].resize(_mapHeight);

        for (size_t row = 0; row < _mapHeight; ++row)
        {
            _tileMapGrid[layer][row].resize(_mapWidth);

            for (size_t col = 0; col < _mapWidth; ++col)
            {
                Tile* tile = new Tile(texture);
                _tileMapGrid[layer][row][col] = tile;
            }
        }

        // FILL ONLY DEFINED TILES FROM JSON
        const auto& tilesJson = data[LayersName][layer][tileName];
        for (const auto& tileJson : tilesJson)
        {
            unsigned int spriteSheetID = stoi(tileJson[IdName].get<string>());
            unsigned int col = tileJson[ColName];
            unsigned int row = tileJson[RowName];

            Tile* tile = _tileMapGrid[layer][row][col];

            tile->SetSpriteSheetID(spriteSheetID);
            tile->SetID(id);

            // APPLY COLLISION FROM LAYER
            tile->SetCollide(layerHasCollision);

            SetTileUV(*tile, spriteSheetID);

            ++id;
        }
    }

    UpdateTilesPositions();
}


void TileMap::UpdateTilesPositions()
{
    Window* window = GetWindow();
    if (!window) return;

    const float windowWidth = static_cast<float>(window->GetWidth());
    const float windowHeight = static_cast<float>(window->GetHeight());

    const float scaledTileWidth = windowWidth / static_cast<float>(_mapWidth);
    const float scaledTileHeight = windowHeight / static_cast<float>(_mapHeight);

    for (size_t layer = 0; layer < _tileMapGrid.size(); ++layer)
    {
        for (unsigned int row = 0; row < _mapHeight; ++row)
        {
            for (unsigned int col = 0; col < _mapWidth; ++col)
            {
                Tile* tile = _tileMapGrid[layer][row][col];

                tile->SetScale(Vector3{ scaledTileWidth, scaledTileHeight, 1 });

                float posX = (scaledTileWidth / 2.0f) + (scaledTileWidth * col);
                float posY = windowHeight - (scaledTileHeight / 2.0f) - (scaledTileHeight * row);

                tile->SetPosition(Vector3{ posX, posY, 0 });
            }
        }
    }
}

void TileMap::SetTileUV(Tile& tile, unsigned int id)
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

#include "Tile.h"

Tile::Tile() : Sprite(0)
{
	SetUVCordinates(Vector2{ 0,0 }, Vector2{ 1,1 }); // UV por defecto
}

Tile::Tile(unsigned int texture) : Sprite(texture)
{
	SetUVCordinates(Vector2{ 0,0 }, Vector2{ 1,1 }); // UV por defecto
}

Tile::~Tile()
{
}

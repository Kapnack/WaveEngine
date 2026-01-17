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

void Tile::SetCollide(bool walkable)
{
	this->collide = walkable;
}

bool Tile::CanCollide()
{
	return collide;
}

void Tile::SetID(unsigned int id)
{
	this->id = id;
}

unsigned int Tile::GetID()
{
	return id;
}

void Tile::SetSpriteSheetID(int id)
{
	spriteSheetID = id;
}

unsigned int Tile::GetSpriteSheetID()
{
	return spriteSheetID;
}
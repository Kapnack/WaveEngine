#include "Tile.h"

Tile::Tile() : Sprite(0)
{
}

Tile::Tile(unsigned int texture) : Sprite(texture)
{
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
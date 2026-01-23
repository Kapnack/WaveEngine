#include "Tile.h"

Tile::Tile(const unsigned int& ID) : Sprite(ID)
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

void Tile::SetTileID(unsigned int id)
{
	this->tileID = id;
}

unsigned int Tile::GetID()
{
	return tileID;
}

void Tile::SetSpriteSheetID(int id)
{
	spriteSheetID = id;
}

unsigned int Tile::GetSpriteSheetID()
{
	return spriteSheetID;
}
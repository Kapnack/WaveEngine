#include "Tile.h"

namespace WaveEngine
{
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

	bool Tile::CanCollide() const
	{
		return collide;
	}

	void Tile::SetTileID(unsigned int id)
	{
		this->tileID = id;
	}

	unsigned int Tile::GetTileID() const
	{
		return tileID;
	}

	void Tile::SetSpriteSheetID(int id)
	{
		spriteSheetID = id;
	}

	unsigned int Tile::GetSpriteSheetID() const
	{
		return spriteSheetID;
	}
}
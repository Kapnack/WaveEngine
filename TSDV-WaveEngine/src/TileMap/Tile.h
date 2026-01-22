#pragma once

#include "Entity/Entity2D/Sprite/Sprite.h"

class Tile : public Sprite
{
private:

	int spriteSheetID = -1;
	unsigned int id = 0;
	bool collide = false;

public:

	Tile();
	~Tile();

	bool CanCollide();
	void SetCollide(bool walkable);

	void SetID(unsigned int id);
	unsigned int GetID();

	void SetSpriteSheetID(int id);
	unsigned int GetSpriteSheetID();
};


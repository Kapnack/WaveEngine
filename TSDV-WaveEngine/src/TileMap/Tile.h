#pragma once

#include "Entity/Entity2D/Sprite/Sprite.h"

class TileMap;
class EntityManager;
class EntityFactory;

class Tile : public Sprite
{
private:

	int spriteSheetID = -1;
	unsigned int tileID = 0;
	bool collide = false;

	Tile(const unsigned int& ID);
	~Tile();

	friend class TileMap;
	friend class EntityManager;
	friend class EntityFactory;

public:

	bool CanCollide();
	void SetCollide(bool walkable);

	void SetTileID(unsigned int id);
	unsigned int GetID();

	void SetSpriteSheetID(int id);
	unsigned int GetSpriteSheetID();
};


#pragma once

#include "BaseGame/BaseGame.h"

#include "TileMap/TileMap.h"

class Game : public BaseGame
{
private:

	TileMap* tileMap;
	Sprite* sprite;
	Sprite* otherThing;

protected:

	void Init() override;
	void Update() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};


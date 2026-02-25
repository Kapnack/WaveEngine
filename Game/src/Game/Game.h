#pragma once

#include "BaseGame/BaseGame.h"
#include "TileMap/TileMap.h"
#include "CollisionManager/CollisionManager.h"
#include "Entity/Controller/EntityController/EntityController.h"

class Game : public BaseGame
{
private:

	unsigned int tileMap;

	unsigned int player;

	int playerVelocity = 100;

	Animation* walkingLeft;
	Animation* walkingUp;
	Animation* walkingDown;
	Animation* walkingRight;

protected:

	void Init(const int& width, const int& height) override;
	void Update() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};


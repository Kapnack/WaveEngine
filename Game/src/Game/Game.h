#pragma once

#include "Entity/Entity2D/Shape/Shape.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
private:

	Vector3 pos;
	Vector3 scale;
	Sprite* character;
	Sprite* obstacle;

	Animation* WalkDown;
	Animation* WalkUp;
	Animation* WalkLeft;
	Animation* WalkRight;

	float timer = 0;

protected:

	void Init() override;
	void Update() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};


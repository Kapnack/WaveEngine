#pragma once

#include "Entity/Entity2D/Shape/Shape.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "Engine/Engine.h"

class Game : public Engine
{
private:

	Vector3 pos;
	Vector3 scale;
	Sprite* sprite;

	Animation* animation;

	float timer = 0;

protected:

	void Init() override;
	void Update() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};


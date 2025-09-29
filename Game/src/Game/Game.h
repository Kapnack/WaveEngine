#pragma once

#include "Entity/Entity2D/Shape/Shape.h"
#include "Engine/Engine.h"

class Game : public Engine
{
private:

	Vector3 pos;
	Vector3 scale;
	Shape* shape;
	Shape* shape2;

protected:

	void Init() override;
	void Update() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};


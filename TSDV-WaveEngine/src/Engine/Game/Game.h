#pragma once

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Engine/Engine.h"

class Game : public Engine
{
private:

	Shape* shape;
	Shape* shape2;

public:

	Game(int width, int height);
	~Game();

	void Init() override;
	void Update() override;
	void Unload() override;
};


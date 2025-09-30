#pragma once

#include "Entity/Entity2D/Shape/Shape.h"
#include "Engine/Engine.h"

class Game : public Engine
{
private:

	Vector3 squarePos;
	Vector3 trianglePos;
	Vector3 scale;
	Shape* shape;
	Shape* shape2;
	bool isGoingUp = true;
	bool isGoingDown = false;

protected:

	void Init() override;
	void Update() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};


#pragma once

#include "Entity/Entity2D/Shape/Shape.h"
#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
private:

	static const int starParts = 2;

	Vector3 pos;
	Vector3 scale;
	Square* blueSquare;
	Square* pinkSquare;
	Triangle* triangle;
	Triangle* star[starParts];

	Vector3 startingScale;
	Vector3 endScale;

	bool shouldScale = true;

	const float movementSpeed = 150;
	const float rotate = -180.0f;

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


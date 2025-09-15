#pragma once

#include "../Shape.h"

WAVEEXPORT class Square : public Shape
{
public:

	WAVEEXPORT Square(Renderer* renderer, Vector3 position, Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
	WAVEEXPORT ~Square();
};


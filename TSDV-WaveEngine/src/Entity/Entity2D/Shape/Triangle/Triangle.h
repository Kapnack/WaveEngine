#pragma once

#include "../Shape.h"

WAVEEXPORT class Triangle : public Shape
{
public:

	WAVEEXPORT Triangle(Renderer* renderer, Vector4 color = {1.0f, 1.0f, 1.0f, 1.0f});
	WAVEEXPORT ~Triangle();
};


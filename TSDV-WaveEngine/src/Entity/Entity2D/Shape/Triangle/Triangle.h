#pragma once

#include "../Shape.h"

WAVEEXPORT class Triangle : public Shape
{
public:

	WAVEEXPORT Triangle(Renderer* renderer, Vector3 position);
	WAVEEXPORT ~Triangle();
};


#pragma once

#include "../Shape.h"

WAVEEXPORT class Square : public Shape
{
public:

	WAVEEXPORT Square(Renderer* renderer, Vector3 position);
	WAVEEXPORT ~Square();
};


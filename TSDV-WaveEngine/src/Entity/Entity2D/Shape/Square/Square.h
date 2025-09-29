#pragma once

#include "../Shape.h"

WAVEEXPORT class Square : public Shape
{
public:

	WAVEEXPORT Square(Renderer* renderer);
	WAVEEXPORT Square(Renderer* renderer, Vector4 color);
	WAVEEXPORT ~Square();
};


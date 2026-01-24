#pragma once

#include "Export.h"

WAVEEXPORT struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2()
	{
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};
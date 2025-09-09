#pragma once

#include "Entity/Entity2D/Entity2D.h"

WAVEEXPORT class Shape : public Entity2D
{
protected:

public:

	WAVEEXPORT Shape(Renderer* renderer, Vector3 position);
	WAVEEXPORT ~Shape();
};


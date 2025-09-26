#pragma once

#include "Entity/Entity.h"

WAVEEXPORT class Entity2D : public Entity
{

public:

	WAVEEXPORT Entity2D(Renderer* renderer, Vector3 position);
	WAVEEXPORT virtual ~Entity2D();
};


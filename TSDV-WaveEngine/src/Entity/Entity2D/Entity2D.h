#pragma once

#include "Entity/Entity.h"

class Entity2D : public Entity
{

public:

	Entity2D(Renderer* renderer, Vector3 position);
	virtual ~Entity2D();

	void Draw() override;
};


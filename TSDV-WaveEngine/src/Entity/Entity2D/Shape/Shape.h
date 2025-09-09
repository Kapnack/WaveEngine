#pragma once

#include "Entity/Entity2D/Entity2D.h"

class Shape : public Entity2D
{
protected:

public:

	Shape(Renderer* renderer, Vector3 position);
	~Shape();

	void Draw() override;
};


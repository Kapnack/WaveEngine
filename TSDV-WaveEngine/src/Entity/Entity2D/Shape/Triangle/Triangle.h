#pragma once

#include "../Shape.h"

class Triangle : public Shape
{
public:

	Triangle(Renderer* renderer, Vector3 position);
	~Triangle();
};


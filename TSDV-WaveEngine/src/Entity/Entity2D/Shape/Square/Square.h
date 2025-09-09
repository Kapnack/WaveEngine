#pragma once

#include "../Shape.h"

class Square : public Shape
{
public:

	Square(Renderer* renderer, Vector3 position);
	~Square();
};


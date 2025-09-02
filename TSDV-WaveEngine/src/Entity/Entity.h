#pragma once

#include "Vector3.h"

class Entity
{
protected:

	Vector3 position;

public:

	Entity();
	virtual ~Entity();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 vector);

	virtual void Draw() = 0;
};


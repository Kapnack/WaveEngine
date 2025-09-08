#pragma once

#include <vector>

#include "Renderer/Renderer.h"
#include "Vector3.h"

class Entity
{
protected:

	Renderer render;
	Vector3 position;

public:

	Entity();
	virtual ~Entity();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 vector);

	virtual void Draw() = 0;
};

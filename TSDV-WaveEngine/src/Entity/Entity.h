#pragma once

#include <vector>

#include "Export.h"
#include "Renderer/Renderer.h"
#include "Vector3.h"

class Entity
{
protected:

	Renderer* renderer;
	Vector3 position;

	unsigned int VAO;

	unsigned int VBO;
	float* vertex;
	int vertexSize;

	unsigned int EBO;
	int* indices;
	int indexSize;

public:

	Entity(Renderer* renderer, Vector3 position);
	virtual ~Entity();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 vector);

	virtual void Draw() = 0;
};

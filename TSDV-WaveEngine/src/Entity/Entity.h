#pragma once

#include <vector>

#include "Export.h"
#include "Renderer/Renderer.h"
#include "VertexPosColor.h"

WAVEEXPORT class Entity
{
protected:

	Renderer* renderer;
	Vector3 position;

	unsigned int VAO;

	unsigned int VBO;
	VertexPosColor* vertex;
	int vertexSize;

	unsigned int EBO;
	int* indices;
	int indexSize;

public:

	WAVEEXPORT	Entity(Renderer* renderer, Vector3 position);
	WAVEEXPORT virtual ~Entity();

	WAVEEXPORT void SetPosition(float x, float y, float z);
	WAVEEXPORT void SetPosition(Vector3 vector);

	WAVEEXPORT virtual void Draw() = 0;
};

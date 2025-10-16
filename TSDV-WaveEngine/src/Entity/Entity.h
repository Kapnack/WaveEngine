#pragma once

#include <vector>

#include "Export.h"
#include "Renderer/Renderer.h"
#include "VertexData.h"

WAVEEXPORT class Entity
{
protected:

	Renderer* renderer;
	Vector3 position;
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
	float rotation = 0.0f;

	unsigned int VAO;

	unsigned int VBO;
	VertexData* vertex;
	int vertexSize;

	unsigned int EBO;
	int* indices;
	int indexSize;

	glm::mat4 model;

	void SetTRS();

public:

	WAVEEXPORT	Entity(Renderer* renderer);
	WAVEEXPORT virtual ~Entity();

	WAVEEXPORT void Translate(Vector3 translation);
	WAVEEXPORT void Translate(float x, float y);

	WAVEEXPORT void SetPosition(float x, float y);
	WAVEEXPORT void SetPosition(Vector3 vector);

	WAVEEXPORT void SetScale(float x, float y);
	WAVEEXPORT void SetScale(Vector3 vector);

	WAVEEXPORT void Scale(float x, float y);
	WAVEEXPORT void Scale(Vector3 vector);

	WAVEEXPORT void SetRotation(float angle);
	WAVEEXPORT void Rotate(float angle);

	WAVEEXPORT void SetColor(Vector4 color);
	WAVEEXPORT void SetVertexColor(int index, Vector4 color);

	WAVEEXPORT virtual void Draw() = 0;
};

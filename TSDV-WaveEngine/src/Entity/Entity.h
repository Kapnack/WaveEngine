#pragma once

#include <vector>

#include "Export.h"
#include "Renderer/Renderer.h"
#include "VertexData.h"

WAVEEXPORT class Entity
{
protected:

	Renderer* renderer;

	Vector3 translation;
	Vector3 previousPostion;
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

	virtual void SetTRS();

public:

	WAVEEXPORT	Entity(Renderer* renderer);
	WAVEEXPORT virtual ~Entity();

	WAVEEXPORT virtual Vector3 GetPos() = 0;
	WAVEEXPORT virtual Vector3 GetScale() = 0;
	WAVEEXPORT virtual float GetRotation() = 0;

	WAVEEXPORT virtual void Translate(Vector3 translation) = 0;
	WAVEEXPORT virtual void Translate(float x, float y) = 0;

	WAVEEXPORT virtual void SetPosition(float x, float y) = 0;
	WAVEEXPORT virtual void SetPosition(Vector3 vector) = 0;

	WAVEEXPORT virtual void SetScale(float x, float y) = 0;
	WAVEEXPORT virtual void SetScale(Vector3 vector) = 0;

	WAVEEXPORT virtual void Scale(float x, float y) = 0;
	WAVEEXPORT virtual void Scale(Vector3 vector) = 0;

	WAVEEXPORT virtual void SetRotation(float angle) = 0;
	WAVEEXPORT virtual void Rotate(float angle) = 0;

	WAVEEXPORT virtual void SetColor(Vector4 color) = 0;
	WAVEEXPORT virtual void SetVertexColor(int index, Vector4 color) = 0;

	WAVEEXPORT virtual void Draw() = 0;
};

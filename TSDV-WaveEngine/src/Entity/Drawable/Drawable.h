#pragma once

#include "Export.h"
#include "VertexData.h"
#include "Renderer/Renderer.h"

class MeshImGui;

WAVEEXPORT class Drawable
{
private:

	void UpdateVertexBuffer();

	friend class MeshImGui;

protected:

	unsigned int ID;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int layer = 0;

	VertexData* vertex;
	int vertexSize;

	int* indices;
	int indexSize;

	Renderer* GetRenderer() const;

	Drawable(const unsigned int& ID);
	~Drawable();

public:

	WAVEEXPORT void SetLayer(const int& layer);
	WAVEEXPORT int GetLayer() const;

	WAVEEXPORT void SetColor(const Vector4& color);
	WAVEEXPORT void SetVertexColor(const int& index, const Vector4& color);

	WAVEEXPORT virtual void Draw() = 0;
};


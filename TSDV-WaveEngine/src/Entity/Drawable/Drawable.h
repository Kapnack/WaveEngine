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

	unsigned int ID;

	unsigned int layer;

protected:

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int materialID;

	VertexData* vertex;
	int vertexSize;

	int* indices;
	int indexSize;

	MaterialManager* GetMaterialManager();

	Renderer* GetRenderer() const;

	Drawable(const unsigned int& ID);
	~Drawable();

public:

	WAVEEXPORT void SetLayer(const int& layer);
	WAVEEXPORT int GetLayer() const;

	WAVEEXPORT void SetMaterial(unsigned int materialID);
	WAVEEXPORT const unsigned int GetMaterial() const;

	WAVEEXPORT void SetColor(const Vector4& color);
	WAVEEXPORT void SetVertexColor(const int& index, const Vector4& color);

	WAVEEXPORT virtual void Draw() = 0;
};


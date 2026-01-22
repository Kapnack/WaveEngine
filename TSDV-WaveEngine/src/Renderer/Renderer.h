#pragma once

#include "ServiceProvider/Service.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window/Window.h"

#include "VertexData.h"
#include "Material/Material.h"

class Renderer final : public Service
{
private:

	glm::mat4* view;
	glm::mat4* proj;

	void Init();
	void Unload();

	Vector3 res;

	const unsigned int ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack);

	Window* GetWindow();

	MaterialManager* GetMaterialManager();

public:

	Renderer();
	~Renderer();

	unsigned int shapeShaders;
	unsigned int spriteShaders;

	void CreateBuffers(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const;
	void CreateBuffersSprite(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const;

	void UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

	void Clear();

	Vector3 GetRes();

	static float GetGLTime();

	void DrawElement(glm::mat4& model, unsigned int materialID, int indicesSize, unsigned int VAO);
	void DrawElementSprite(glm::mat4& model, unsigned int materialID, int indicesSize, unsigned int VAO, unsigned int texture);
};


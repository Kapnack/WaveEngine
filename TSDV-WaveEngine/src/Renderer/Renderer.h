#pragma once

#include "ServiceProvider/Service.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window/Window.h"

#include "VertexData.h"
#include "Material/Material.h"

class Renderer : public Service
{
private:

	glm::mat4* view;
	glm::mat4* proj;

	void Init();
	void Unload();

	Vector3 res;

	Material* ReturnWorkingMaterial(Material* materialToTry, Material* fallBack);

	Window* GetWindow();

public:

	Renderer();
	~Renderer();

	Material* shapeShaders;
	Material* spriteShaders;

	void CreateBuffers(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const;
	void CreateBuffersSprite(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO, const unsigned int& texture) const;

	void UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

	void Clear();

	Vector3 GetRes();

	static float GetGLTime();

	void DrawElement(glm::mat4& model, Material* material, int indicesSize, unsigned int VAO);
	void DrawElementSprite(glm::mat4& model, Material* material, int indicesSize, unsigned int VAO, unsigned int texture);
};


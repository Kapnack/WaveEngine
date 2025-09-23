#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexData.h"
#include "Material/Material.h"

class Renderer
{
private:

	void Init(int width, int height);
	void Unload();

public:

	Material* shader;

	void CreateBuffers(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO,
		unsigned& VBO,
		unsigned& EBO);

	void DrawElement(glm::mat4& model, int indicesSize, unsigned int VAO);

	Renderer(int width, int height);
	~Renderer();
};


#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexData.h"
#include "Material/Material.h"

class Renderer
{
private:

	glm::mat4* view;
	glm::mat4* proj;

	void Init(int width, int height);
	void Unload();

public:

	Renderer(int width, int height);
	~Renderer();

	Material* shader;

	void CreateBuffers(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO,
		unsigned& VBO,
		unsigned& EBO);

	void Clear();

	void DrawElement(glm::mat4& model, int indicesSize, unsigned int VAO);
};


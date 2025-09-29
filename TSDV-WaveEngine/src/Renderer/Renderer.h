#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window/Window.h"

#include "VertexData.h"
#include "Material/Material.h"

class Renderer
{
private:

	Window* window;

	glm::mat4* view;
	glm::mat4* proj;

	void Init();
	void Unload();

	Vector3 res;

public:

	Renderer(Window* window);
	~Renderer();

	Material* shader;

	void CreateBuffers(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO,
		unsigned& VBO,
		unsigned& EBO);

	void Clear();

	Vector3 GetRes();

	static float GetGLTime();

	void DrawElement(glm::mat4& model, int indicesSize, unsigned int VAO);
};


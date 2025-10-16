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

	Material* shapeShaders;
	Material* spriteShaders;

	void CreateBuffers(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO,
		unsigned& VBO,
		unsigned& EBO);
	void CreateBuffersSprite(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO, unsigned int& texture);

	void UpdateColorBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

	void Clear();

	Vector3 GetRes();

	static float GetGLTime();

	void DrawElement(glm::mat4& model, int indicesSize, unsigned int VAO);
	void DrawElementSprite(glm::mat4& model, int indicesSize, unsigned int VAO, unsigned int texture);
};


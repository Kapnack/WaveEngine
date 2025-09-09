#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BufferData.h"
#include "Material/Material.h"

class Renderer
{
private:

	void Init();
	void Unload();

public:

	Material shader;

	void CreateBuffers(float* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO,
		unsigned& VBO,
		unsigned& EBO);

	void DrawElement(int indicesSize, unsigned int VAO);

	Renderer();
	~Renderer();
};


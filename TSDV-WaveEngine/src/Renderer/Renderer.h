#pragma once

#include "Shader/Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Renderer
{
private:

	Shader shader;

public:

	void Init(float position[], unsigned int indices[]);
	void Unload();

	Renderer();
	~Renderer();
};


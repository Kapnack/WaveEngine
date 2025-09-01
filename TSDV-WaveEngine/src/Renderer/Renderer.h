#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader/Shader.h"

class Renderer
{
private:

	unsigned int shader;

public:

	void Init(float position[]);

	void Unload();

	Renderer();
	Renderer();
	~Renderer();
};


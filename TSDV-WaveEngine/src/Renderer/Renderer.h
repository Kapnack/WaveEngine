#pragma once

#include "Shader/Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Renderer
{
private:

	unsigned int shader;

public:

	void Init(float position[]);

	void Unload();

	Renderer();
	~Renderer();
};


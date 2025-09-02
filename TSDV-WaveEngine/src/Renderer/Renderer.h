#pragma once

#include "Material/Material.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Renderer
{
private:

	Material shader;

public:

	void Init(float position[], unsigned int indices[]);
	void Unload();

	Renderer();
	~Renderer();
};


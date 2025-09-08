#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BufferData.h"
#include "Material/Material.h"

class Renderer
{
private:



public:

	Material shader;

	void Init();
	void Unload();

	void DrawElement();

	Renderer();
	~Renderer();
};


#pragma once

#include <GLFW/glfw3.h>

#include "Window/Window.h"

class Renderer
{
private:

	Window* window;

public:

	void Init();

	void Update();

	Renderer();
	Renderer(Window& window);
	~Renderer();
};

 
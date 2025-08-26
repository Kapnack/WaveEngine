#pragma once

#include <glfw3.h>

#include "Window/Window.h"

class Renderer
{
private:

	Window* window;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:

	void Init();

	void Update();

	Renderer();
	Renderer(Window& window);
	~Renderer();
};

 
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:

	GLFWwindow* window = nullptr;

	int width = 0;
	int height = 0;
	const char* title;
	GLFWmonitor* monitor;
	GLFWwindow* share;

	void Init();
	void Unload();

public:

	Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	~Window();

	GLFWwindow* GetWindow();
	int GetWidth();
	int GetHeight();

	void SwapBuffer();
	void HandleInput();
};


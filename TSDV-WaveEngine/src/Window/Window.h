#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

WAVEEXPORT class Window : public Service
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

	static void FrameBufferCallBack(GLFWwindow* window, int width, int height);

public:

	WAVEEXPORT Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	WAVEEXPORT ~Window();

	GLFWwindow* GetGLFWindow();
	WAVEEXPORT int GetWidth();
	WAVEEXPORT int GetHeight();

	WAVEEXPORT void SwapBuffer();
	WAVEEXPORT void HandleInput();

	WAVEEXPORT float GetGLTime();
};


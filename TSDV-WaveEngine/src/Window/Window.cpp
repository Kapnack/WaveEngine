#include "Window.h"

#include <iostream>

using namespace std;

Window::~Window()
{
	Unload();
}

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = monitor;
	this->share = share;

	Init();
}

void Window::Init()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

		exit(-1);
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		cout << "GLEW FAILED TO INIT!!!";
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}


void Window::Unload()
{
	glfwTerminate();
}

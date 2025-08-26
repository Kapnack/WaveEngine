#include "Window.h"
#include <iostream>

using namespace std;

Window::Window()
{
}

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = monitor;
	this->share = share;
}

Window::~Window()
{
}

void Window::Init()
{
	if (!glfwInit())
		exit(-1);

	window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

		exit(-1);
	}

	glfwMakeContextCurrent(window);
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

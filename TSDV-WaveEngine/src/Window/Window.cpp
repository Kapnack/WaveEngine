#include "Window.h"

#include <iostream>

using namespace std;

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) : Service()
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = monitor;
	this->share = share;

	baseWidth = width;
	baseHeight = height;

	Init();
}

Window::~Window()
{
	Unload();
}

void Window::Init()
{
	//Adding hints for the window that is going to be created.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Vercion Mayor number 3.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// Vercion Minor number 0.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Sets up the profile that is going to be use for this Project.
	//In this case GLFW_OPENGL_CORE_PROFILE. This doesn't allow old OpenGL functions.
	//Example: glBegin(), glEnd(), glVertex3f(). So you are force on using VAO, VBO, EBO.

	// Creates the window based on the parameter it recieves and the hints given.
	window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, Window::FrameBufferCallBack);

	if (glewInit() != GLEW_OK)
		cout << "GLEW FAILED TO INIT!!!";
}

GLFWwindow* Window::GetGLFWindow()
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

int Window::GetBaseWidth()
{
	return baseWidth;
}

int Window::GetBaseHeight()
{
	return baseHeight;
}

void Window::SwapBuffer()
{
	glfwSwapBuffers(window);
}

void Window::HandleInput()
{
	glfwPollEvents();
}

float Window::GetGLTime()
{
	return static_cast<float>(glfwGetTime());
}

void Window::Unload()
{
	glfwTerminate();
}

void Window::FrameBufferCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (!win)
		return;

	win->width = width;
	win->height = height;
}

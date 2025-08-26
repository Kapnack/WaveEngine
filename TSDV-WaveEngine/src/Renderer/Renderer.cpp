#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::Renderer(Window& window)
{
	this->window = &window;
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
	glViewport(0, 0, window->GetWidth(), window->GetHeight());
}

void Renderer::Update()
{
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}

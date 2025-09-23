#include "Engine.h"

void Engine::InitEngine(int width, int height)
{
	if (!glfwInit())
		exit(-1);

	window = new Window(width, height, "WaveEngine", nullptr, nullptr);
	renderer = new Renderer(width, height);
}

void Engine::EndEngine()
{
	delete renderer;
	delete window;
}

Renderer* Engine::GetRenderer()
{
	return renderer;
}

Engine::Engine(int width, int height)
{
	InitEngine(width, height);
}

Engine::~Engine()
{
	EndEngine();
}

void Engine::Run()
{
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(renderer->shader->GetProgram());

		Update();

		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}

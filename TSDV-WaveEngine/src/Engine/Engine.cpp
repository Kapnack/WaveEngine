#include "Engine.h"

void Engine::InitEngine(int width, int height)
{
	this->width = width;
	this->height = height;

	if (!glfwInit())
		exit(-1);

	window = new Window(width, height, "WaveEngine", nullptr, nullptr);
	renderer = new Renderer(window);
	time = new Time(window);
}

void Engine::EndEngine()
{
	delete time;
	delete renderer;
	delete window;
}

Renderer* Engine::GetRenderer()
{
	return renderer;
}

float Engine::GetDeltaTime()
{
	return time->GetDeltaTime();
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
		time->SetDeltaTime();

		renderer->Clear();

		Update();

		window->SwapBuffer();
		window->HandleInput();
	}
}

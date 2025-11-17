#include "BaseGame.h"
#include "Input/Input.h"

void BaseGame::InitEngine(int width, int height)
{
	this->width = width;
	this->height = height;

	if (!glfwInit())
		exit(-1);

	window = new Window(width, height, "WaveEngine", nullptr, nullptr);
	renderer = new Renderer(window);

	Input::SetWindow(window);
}

void BaseGame::EndEngine()
{
	delete renderer;
	delete window;
}

Renderer* BaseGame::GetRenderer()
{
	return renderer;
}

float BaseGame::GetDeltaTime()
{
	return Time::GetDeltaTime();
}

BaseGame::BaseGame(int width, int height)
{
	InitEngine(width, height);
}

BaseGame::~BaseGame()
{
	EndEngine();
}

void BaseGame::Run()
{
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		Time::SetDeltaTime();

		renderer->Clear();

		Update();

		window->SwapBuffer();
		window->HandleInput();
	}
}

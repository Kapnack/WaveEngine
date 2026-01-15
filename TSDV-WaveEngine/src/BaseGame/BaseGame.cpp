#include "BaseGame.h"
#include "Input/Input.h"

#include "ServiceProvider/ServiceProvider.h"

void BaseGame::InitEngine(int width, int height)
{
	this->width = width;
	this->height = height;

	if (!glfwInit())
		exit(-1);

	ServiceProvider::Register(new MaterialManager());

	window = new Window(width, height, "WaveEngine", nullptr, nullptr);

	ServiceProvider::TryGet<MaterialManager>()->Init();
	
	renderer = new Renderer(window);

	ServiceProvider::Register(new Input(window));
	ServiceProvider::Register(new Time(window));
	
}

void BaseGame::EndEngine()
{
	delete renderer;
	delete window;

	ServiceProvider::Clear();
}

Time* BaseGame::GetTime()
{
	return ServiceProvider::TryGet<Time>();
}

Renderer* BaseGame::GetRenderer()
{
	return renderer;
}

float BaseGame::GetDeltaTime()
{
	return ServiceProvider::Get<Time>()->GetDeltaTime();
}

Input* BaseGame::GetInput()
{
	return ServiceProvider::Get<Input>();
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
		GetTime()->SetDeltaTime();

		renderer->Clear();

		Update();

		window->SwapBuffer();
		window->HandleInput();
	}
}

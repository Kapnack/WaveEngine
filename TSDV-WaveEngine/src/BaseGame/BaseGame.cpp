#include "BaseGame.h"
#include "Input/Input.h"

#include "ServiceProvider/ServiceProvider.h"

void BaseGame::InitEngine(int width, int height)
{
	this->width = width;
	this->height = height;

	if (!glfwInit())
		exit(-1);

	ServiceProvider::Instance().Register(new MaterialManager());

	window = new Window(width, height, "WaveEngine", nullptr, nullptr);

	ServiceProvider::Instance().TryGet<MaterialManager>()->Init();
	
	renderer = new Renderer(window);

	ServiceProvider::Instance().Register(new Input(window));
	ServiceProvider::Instance().Register(new Time(window));
	
}

void BaseGame::EndEngine()
{
	delete renderer;
	delete window;

	ServiceProvider::Instance().Clear();
}

Time* BaseGame::GetTime()
{
	return ServiceProvider::Instance().TryGet<Time>();
}

Renderer* BaseGame::GetRenderer()
{
	return renderer;
}

float BaseGame::GetDeltaTime()
{
	return ServiceProvider::Instance().Get<Time>()->GetDeltaTime();
}

Input* BaseGame::GetInput()
{
	return ServiceProvider::Instance().Get<Input>();
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

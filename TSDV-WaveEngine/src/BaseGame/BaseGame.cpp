#include "BaseGame.h"
#include "Input/Input.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"

BaseGame::BaseGame(int width, int height)
{
	InitEngine(width, height);
}

BaseGame::~BaseGame()
{
	EndEngine();
}

void BaseGame::InitEngine(int width, int height)
{
	if (!glfwInit())
		exit(-1);

	ServiceProvider::Instance().Register(new Window(width, height, "WaveEngine", nullptr, nullptr));
	ServiceProvider::Instance().Register(new MaterialManager());
	ServiceProvider::Instance().Register(new MaterialFactory());
	ServiceProvider::Instance().Register(new Renderer());
	ServiceProvider::Instance().Register(new Input());
	ServiceProvider::Instance().Register(new Time());
}

void BaseGame::EndEngine()
{
	ServiceProvider::Instance().Clear();
}

Time* BaseGame::GetTime()
{
	return ServiceProvider::Instance().TryGet<Time>();
}

Renderer* BaseGame::GetRenderer()
{
	return ServiceProvider::Instance().Get<Renderer>();
}

float BaseGame::GetDeltaTime()
{
	return ServiceProvider::Instance().Get<Time>()->GetDeltaTime();
}

Window* BaseGame::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

Input* BaseGame::GetInput()
{
	return ServiceProvider::Instance().Get<Input>();
}

void BaseGame::Run()
{
	while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
	{
		GetTime()->SetDeltaTime();

		GetRenderer()->Clear();

		Update();

		GetWindow()->SwapBuffer();
		GetWindow()->HandleInput();
	}
}

#include "BaseGame.h"
#include "Input/Input.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"

BaseGame::BaseGame(int width, int height)
{
}

BaseGame::~BaseGame()
{
}

void BaseGame::Init(int width, int height)
{
	if (!glfwInit())
		exit(-1);

	ServiceProvider::Instance().Register(new Window(width, height, "WaveEngine", nullptr, nullptr));

	ServiceProvider::Instance().Register(new MaterialManager());
	ServiceProvider::Instance().Register(new MaterialFactory());
	ServiceProvider::Instance().Register(new EntityManager());
	ServiceProvider::Instance().Register(new EntityFactory(GetEntityManager()));
	ServiceProvider::Instance().Register(new Renderer());
	ServiceProvider::Instance().Register(new Input());
	ServiceProvider::Instance().Register(new Time());

}

void BaseGame::EndEngine()
{
	ServiceProvider::Instance().Clear();
}

void BaseGame::EngineDraw()
{
	GetEntityManager()->DrawEntities();
}

Time* BaseGame::GetTime()
{
	return ServiceProvider::Instance().Get<Time>();
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

MaterialManager* BaseGame::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

MaterialFactory* BaseGame::GetMaterialFactory()
{
	return ServiceProvider::Instance().Get<MaterialFactory>();
}

Input* BaseGame::GetInput()
{
	return ServiceProvider::Instance().Get<Input>();
}

EntityManager* BaseGame::GetEntityManager()
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

EntityFactory* BaseGame::GetEntityFactory()
{
	return ServiceProvider::Instance().Get<EntityFactory>();
}

void BaseGame::Run()
{
	while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
	{
		GetTime()->SetDeltaTime();

		GetRenderer()->Clear();

		Update();

		EngineDraw();

		Draw();

		GetWindow()->SwapBuffer();
		GetWindow()->HandleInput();
	}

	EndEngine();
}

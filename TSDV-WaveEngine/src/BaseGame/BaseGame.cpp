#include "BaseGame.h"

#include "Input/Input.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "TextureImporter/TextureImporter.h"
#include "TextureImporter/TextureManager.h"

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
	ServiceProvider::Instance().Register(new ImGuiClass());
	ServiceProvider::Instance().Register(new MaterialManager());
	ServiceProvider::Instance().Register(new MaterialFactory());
	ServiceProvider::Instance().Register(new TextureManager());
	ServiceProvider::Instance().Register(new TextureImporter());
	ServiceProvider::Instance().Register(new EntityManager(GetMaterialManager()));
	ServiceProvider::Instance().Register(new EntityFactory(GetEntityManager(), GetImGuiClass(), GetMaterialManager()));
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
	GetImGuiClass()->Draw();
	//GetEntityManager()->DrawEntities();
}

Time* BaseGame::GetTime()
{
	return ServiceProvider::Instance().Get<Time>();
}

Renderer* BaseGame::GetRenderer()
{
	return ServiceProvider::Instance().Get<Renderer>();
}

ImGuiClass* BaseGame::GetImGuiClass()
{
	return ServiceProvider::Instance().Get<ImGuiClass>();
}

float BaseGame::GetDeltaTime()
{
	return GetTime()->GetDeltaTime();
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

TextureManager* BaseGame::GetTextureManager()
{
	return ServiceProvider::Instance().Get<TextureManager>();
}

TextureImporter* BaseGame::GetTextureImporter()
{
	return ServiceProvider::Instance().Get<TextureImporter>();
}

void BaseGame::Run()
{
	try
	{
		while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
		{
			GetTime()->SetDeltaTime();

			GetRenderer()->Clear();

			GetImGuiClass()->Update();

			Update();

			Draw();

			EngineDraw();

			GetWindow()->SwapBuffer();
			GetWindow()->HandleInput();
		}
	}
	catch (exception& e)
	{
		cerr << e.what();
	}
	catch (...)
	{
		cerr << "WAVEENGINE: Unknow Error detected.";
	}

	EndEngine();
}

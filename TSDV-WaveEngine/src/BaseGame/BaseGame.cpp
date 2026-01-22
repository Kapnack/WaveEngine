#include "BaseGame.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(GetWindow()->GetGLFWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

}

void BaseGame::EndEngine()
{
	ServiceProvider::Instance().Clear();
}

void BaseGame::EngineDraw()
{
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
	try
	{
		while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
		{
			GetTime()->SetDeltaTime();

			GetRenderer()->Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			Update();

			EngineDraw();

			Draw();

			ImGui::Begin

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

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	EndEngine();
}

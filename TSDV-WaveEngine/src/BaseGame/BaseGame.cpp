#include "BaseGame.h"

#include "Input/Input.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "TextureImporter/TextureImporter.h"
#include "TextureImporter/TextureManager.h"
#include <Camera/Camera.h>

BaseGame::BaseGame(const int& width, const int& height)
{
	InitEngine(width, height);
}

BaseGame::~BaseGame()
{
	EndEngine();
}

void BaseGame::InitEngine(const int& width, const int& height)
{
	if (!glfwInit())
		exit(-1);

	ServiceProvider::Instance().Register(new Window(width, height, "WaveEngine", nullptr, nullptr));
	ServiceProvider::Instance().Register(new FileReader());
	ServiceProvider::Instance().Register(new MaterialManager());
	ServiceProvider::Instance().Register(new MaterialFactory());
	ServiceProvider::Instance().Register(new TextureManager());
	ServiceProvider::Instance().Register(new TextureImporter());
	ServiceProvider::Instance().Register(new EntityManager(GetMaterialManager()));
	ServiceProvider::Instance().Register(new EntityFactory(GetEntityManager(), GetWindow()));
	ServiceProvider::Instance().Register(new Renderer());
	ServiceProvider::Instance().Register(new Input());
	ServiceProvider::Instance().Register(new Time());
	imGuiClass = new ImGuiClass();

	Camera::camera.SetPosition(397, 392, 1042);
	Camera::camera.SetFarPlane(10000);
	Camera::camera.SetOrthographic(false);
}

void BaseGame::EndEngine()
{
	ServiceProvider::Instance().Clear();
	delete imGuiClass;
}

void BaseGame::Run()
{
	while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
	{
		EngineUpdate();

		Update();

		EngineDraw();

		GetWindow()->SwapBuffer();
		GetWindow()->HandleInput();
	}
}

void BaseGame::EngineUpdate()
{
	if (GetInput()->IsKeyPressed(Keys::W))
	{
		Camera::camera.Translate(Vector3::Up() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	}
	else if (GetInput()->IsKeyPressed(Keys::A))
	{
		Camera::camera.Translate(Vector3::Left() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	}
	else if (GetInput()->IsKeyPressed(Keys::S))
	{
		Camera::camera.Translate(Vector3::Down() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	}
	else if (GetInput()->IsKeyPressed(Keys::D))
	{
		Camera::camera.Translate(Vector3::Right() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	}

	if (GetInput()->IsKeyPressed(Keys::SPACE))
	{
		Camera::camera.Translate(Vector3::Foward() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	}
	else if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
	{
		Camera::camera.Translate(Vector3::Back() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	}

	if (GetInput()->IsKeyPressed(Keys::Q))
		Camera::camera.AddToFarPlane(GetDeltaTime() * Camera::camera.GetMovementSpeed());
	if (GetInput()->IsKeyPressed(Keys::E))
		Camera::camera.AddToFarPlane(GetDeltaTime() * -Camera::camera.GetMovementSpeed());

	if (GetInput()->IsKeyPressed(Keys::Z))
		Camera::camera.Rotate(Vector3::Right() * GetDeltaTime() * Camera::camera.GetMovementSpeed());
	else if (GetInput()->IsKeyPressed(Keys::X))
		Camera::camera.Rotate(Vector3::Left() * GetDeltaTime() * Camera::camera.GetMovementSpeed());

	GetTime()->UpdateDeltaTime();

	imGuiClass->Update();

	if (ServiceProvider::Instance().TryGet<EntityController>())
		ServiceProvider::Instance().Get<EntityController>()->Update(GetDeltaTime());
}

void BaseGame::EngineDraw()
{
	GetRenderer()->Clear();
	GetEntityManager()->DrawEntities();
	imGuiClass->Draw();
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

FileReader* BaseGame::GetFileReader()
{
	return ServiceProvider::Instance().Get<FileReader>();
}

CollisionManager* BaseGame::GetCollsionManager()
{
	return ServiceProvider::Instance().Get<CollisionManager>();
}

void BaseGame::CreateCollisionManager()
{
	ServiceProvider::Instance().Register(new CollisionManager);
}

void BaseGame::DestroyCollisionManager()
{
	ServiceProvider::Instance().UnRegister<CollisionManager>();
}

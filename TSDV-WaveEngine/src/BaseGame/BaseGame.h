#pragma once

#include "Export.h"
#include "Window/Window.h"
#include "ImGuiClass/ImGuiClass.h"
#include "Renderer/Renderer.h"
#include "Time/Time.h"
#include "Input/Input.h"
#include "Material/MaterialManager.h"
#include "FileReader/FileReader.h"
#include "Entity/EntityManager.h"
#include "Entity/EntityFactory.h"

WAVEEXPORT class BaseGame
{
private:

	void EndEngine();

	void EngineDraw();

	Renderer* GetRenderer();

	ImGuiClass* GetImGuiClass();

protected:

	WAVEEXPORT	virtual void Init(int width, int height);
	WAVEEXPORT	virtual void Update() = 0;
	WAVEEXPORT	virtual void Draw() = 0;
	WAVEEXPORT	virtual void Unload() = 0;

	WAVEEXPORT float GetDeltaTime();

	WAVEEXPORT MaterialManager* GetMaterialManager();
	WAVEEXPORT MaterialFactory* GetMaterialFactory();
	WAVEEXPORT Input* GetInput();
	WAVEEXPORT Window* GetWindow();
	WAVEEXPORT Time* GetTime();
	WAVEEXPORT EntityManager* GetEntityManager();
	WAVEEXPORT EntityFactory* GetEntityFactory();
	WAVEEXPORT TextureManager* GetTextureManager();
	WAVEEXPORT TextureImporter* GetTextureImporter();
	WAVEEXPORT FileReader* GetFileReader();

public:

	WAVEEXPORT BaseGame(int width, int height);
	WAVEEXPORT virtual ~BaseGame();

	WAVEEXPORT	void Run();
};


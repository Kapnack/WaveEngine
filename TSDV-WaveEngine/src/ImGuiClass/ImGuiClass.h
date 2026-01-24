#pragma once

#include "ServiceProvider/Service.h"

#include "ServiceProvider/ServiceProvider.h"
#include "TextureImporter/TextureManager.h"
#include "Material/MaterialManager.h"
#include "TextureImporter/Texture.h"
#include "Entity/EntityManager.h"
#include "Window/Window.h"
#include "Vector3.h"
#include "Vector4.h"

#include <string>

#include <vector>

using namespace std;

class BaseGame;

struct ImGuiClassData
{
	unsigned int id;
	Vector3* position = nullptr;
	Vector3* rotation = nullptr;
	unsigned int* textureID = nullptr;
};

enum class ImGuiClassStates
{
	Begin,
	ShowEntities,
	ShowTextures,
	ShowMaterials,
	End
};

class ImGuiClass : public Service
{
private:

	vector<ImGuiClassData*> dataToDraw;

	Window* GetWindow();

	TextureManager* GetTextureManager();
	EntityManager* GetEntityManager();
	MaterialManager* GetMaterialManager();

	short currentState = (short)ImGuiClassStates::ShowEntities;

	void Init();
	void Update();
	void Draw();
	void Unload();

	void GoToPreviousState();
	void GoToNextState();

	ImGuiClass();
	~ImGuiClass();

	friend class BaseGame;
	friend class ServiceProvider;

public:

	WAVEEXPORT void CreateEditor(const unsigned int& ID, Vector3& position, Vector3& rotation, unsigned int* textureID = nullptr);
};
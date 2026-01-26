#pragma once

#include "ServiceProvider/Service.h"

#include "Window/Window.h"
#include "Input/Input.h"
#include "ImGuiClassStates/ImGuiClassState.h"
#include "ImGuiClassStates/TexturesImGui/TexturesImGui.h"
#include "ImGuiClassStates/EntitiesImGui/EntitiesImGui.h"
#include "ImGuiClassStates/MaterialsImGui/MaterialsImGui.h"
#include "ImGuiClassStates/MeshImGui/MeshImGui.h"
#include "Vector3.h"
#include "Vector4.h"

#include <string>
#include <vector>

using namespace std;

class BaseGame;

class ImGuiClass : public Service
{
private:

	EntitiesImGui* showEntitiesState;
	TexturesImGui* showTexturesState;
	MaterialsImGui* showMaterialsState;
	MeshImGui* showMeshState;

	ImGuiClassState* state;

	Window* GetWindow();

	Input* GetInput();

	bool isActive = false;

	void Init();
	void Update();
	void Draw();
	void Unload();

	ImGuiClass();
	~ImGuiClass();

	friend class BaseGame;
	friend class ServiceProvider;
};
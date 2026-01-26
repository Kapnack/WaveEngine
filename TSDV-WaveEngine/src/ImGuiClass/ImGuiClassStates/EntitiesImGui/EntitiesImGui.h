#pragma once

#include "../ImGuiClassState.h"

#include "ImGuiClass/ImGuiClass.h"

#include "Material/MaterialManager.h"
#include "TextureImporter/TextureManager.h"
#include "Entity/EntityManager.h"

class EntitiesImGui : public ImGuiClassState
{
private:

	EntityManager* GetEntityManager();
	MaterialManager* GetMaterialManager();
	TextureManager* GetTextureManager();

	bool showMaterials = false;
	bool showTextures = false;

	int textureID = 0;
	int materialID = 0;

public:

	EntitiesImGui();
	~EntitiesImGui();

	void Update() override;
};


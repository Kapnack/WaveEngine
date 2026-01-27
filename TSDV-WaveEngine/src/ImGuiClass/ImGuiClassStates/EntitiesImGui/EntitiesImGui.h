#pragma once

#include "../ImGuiClassState.h"

#include "ImGuiClass/ImGuiClass.h"

#include "Material/MaterialManager.h"
#include "TextureImporter/TextureManager.h"
#include "Entity/EntityManager.h"
#include "Entity/EntityFactory.h"

class EntitiesImGui : public ImGuiClassState
{
private:

	EntityManager* GetEntityManager();
	EntityFactory* GetEntityFactory();
	MaterialManager* GetMaterialManager();
	TextureManager* GetTextureManager();

	bool showMaterials = false;
	bool showTextures = false;

	const char* creationOptions[4] =
	{
		"None", "Sprite", "Square", "Triangle"
	};

	int currentCreationOption = 0;

	int textureID = 0;
	int materialID = 0;
	int entityToDelete = 0;

public:

	EntitiesImGui();
	~EntitiesImGui();

	void Update() override;
};


#pragma once

#include "../ImGuiClassState.h"

#include "ImGuiClass/ImGuiClass.h"

#include "Material/MaterialManager.h"
#include "TextureImporter/TextureManager.h"
#include "Entity/EntityManager.h"
#include "Entity/EntityFactory.h"
#include <Entity/Entity2D/Sprite/Sprite.h>

class EntitiesImGui : public ImGuiClassState
{
private:

	EntityManager* GetEntityManager();
	EntityFactory* GetEntityFactory();
	MaterialManager* GetMaterialManager();
	TextureManager* GetTextureManager();

	bool showMaterials = false;
	bool showTextures = false;
	bool showInReverseOrder = false;

	const char* creationOptions[4] =
	{
		"None", "Sprite", "Square", "Triangle"
	};

	int currentCreationOption = 0;

	const char* filters[5] =
	{
		"All Entities", "Sprites", "Squares", "Triangles", "Tiles"
	};

	int currentFilter = 0;

	int textureID = 0;
	int materialID = 0;
	int entityToDelete = 0;

	void ShowEntity(Entity* entity);
	void ShowEntityData(Entity* it);
	void ShowMaterial(Entity* entity);
	void ShowTexture(Sprite* sprite);

	template<EntityManagerStandar T>
	void ShowAllOfType(bool reverse)
	{
		auto& vec = GetEntityManager()->GetAllOfType<T>();

		if (!reverse)
		{
			for (auto id : vec)
				ShowEntity(GetEntityManager()->Get(id));
		}
		else
		{
			for (auto it = vec.rbegin(); it != vec.rend(); ++it)
				ShowEntity(GetEntityManager()->Get(*it));
		}
	}

public:

	EntitiesImGui();
	~EntitiesImGui();

	void Update() override;
};


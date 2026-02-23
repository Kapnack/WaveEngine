#pragma once

#include "../ImGuiClassState.h"

#include "ImGuiClass/ImGuiClass.h"

#include "Entity/Drawable/Drawable.h"

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
	bool changedEntityTRS = false;

	const char* creationOptions[4] =
	{
		"None", "Sprite", "Square", "Triangle"
	};

	int currentCreationOption = 0;

	const char* filters[7] =
	{
		"Entities", "Sprites", "Squares", "Triangles", "Tiles", "Drawables", "TileMaps"
	};

	int currentFilter = 0;

	const char* delitionFilters[8] =
	{
		"By ID", "All Entities", "All Sprites", "All Squares", "All Triangles", "All Tiles", "All Drawables", "All TileMaps"
	};

	int currentDeletionFilter = 0;

	int textureID = 0;
	int materialID = 0;
	int layer = 0;
	int entityToDelete = 0;

	map<unsigned int, Drawable*>::iterator drawableIT;

	void EntityCreator();
	void EntityDeleter();

	void EntityDisplayer();
	void ShowEntity(Entity& entity);
	void ShowEntityData(Entity& it);
	void ShowMaterial(const unsigned int& ID, Drawable& entity);
	void ShowTexture(Sprite& sprite);


	template<EntityManagerGetStandar T>
	void ShowAllOfType()
	{
		vector<unsigned int>& vec = GetEntityManager()->GetAllOfType<T>();

		unsigned int* data = vec.data();
		size_t size = vec.size();

		if (!showInReverseOrder)
		{
			for (unsigned int* it = data; it != data + size; ++it)
				ShowEntity(*GetEntityManager()->Get(*it));
		}
		else
		{
			for (unsigned int* it = data + size; it != data;)
				ShowEntity(*GetEntityManager()->Get(*--it));
		}
	}

public:

	EntitiesImGui();
	~EntitiesImGui();

	void Update() override;
};


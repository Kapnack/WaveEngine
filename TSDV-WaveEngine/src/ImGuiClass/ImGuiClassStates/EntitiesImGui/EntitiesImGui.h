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

	const char* creationOptions[4] =
	{
		"None", "Sprite", "Square", "Triangle"
	};

	int currentCreationOption = 0;

	const char* filters[6] =
	{
		"Entities", "Sprites", "Squares", "Triangles", "Tiles", "Drawables"
	};

	int currentFilter = 0;

	const char* delitionFilters[7] =
	{
		"By ID", "All Entities", "All Sprites", "All Squares", "All Triangles", "All Tiles", "All Drawables"
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
	void ShowEntity(Entity* entity);
	void ShowEntityData(Entity* it);
	void ShowMaterial(const unsigned int& ID, Drawable* entity);
	void ShowTexture(Sprite* sprite);


	template<EntityManagerGetStandar T>
	void ShowAllOfType()
	{
		vector<unsigned int>& vec = GetEntityManager()->GetAllOfType<T>();

		if (!showInReverseOrder)
		{
			for (unsigned int id : vec)
				ShowEntity(GetEntityManager()->Get(id));
		}
		else
		{
			for (vector<unsigned int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
				ShowEntity(GetEntityManager()->Get(*it));
		}
	}

public:

	EntitiesImGui();
	~EntitiesImGui();

	void Update() override;
};


#pragma once

#include "../ImGuiClassState.h"

#include "ImGuiClass/ImGuiClass.h"

#include "Entity/Drawable/Drawable.h"

#include "Material/MaterialManager.h"
#include "TextureImporter/TextureManager.h"
#include "Entity/EntityManager.h"
#include "Entity/EntityFactory.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "Entity/Entity2D/Shape/Square/Square.h"

namespace WaveEngine
{
	struct ComboData
	{
		const char* label;
		std::function<void()> action;
	};

	struct ComoboStruct
	{
		vector<ComboData> options;
		vector<const char*> labels;
		int selected = 0;

		ComoboStruct()
		{
		}

		ComoboStruct(vector<ComboData> options)
		{
			this->options = options;

			for (vector<ComboData>::iterator::value_type option : options)
				labels.push_back(option.label);
		}
	};

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

		ComoboStruct creation;
		ComoboStruct filters;
		ComoboStruct deletionOptions;

		int textureID = 0;
		int materialID = 0;
		int layer = 0;
		int entityToDelete = 0;

		Drawable* drawableIT;

		void EntityCreator();
		void EntityDeleter();

		void EntityDisplayer();
		void ShowEntity(Entity& entity);
		void ShowEntityData(Entity& it);
		void ShowMaterial(const unsigned int& ID, Drawable& entity);
		void ShowTexture(Sprite& sprite);

		void ShowAllEntities()
		{
			if (!showInReverseOrder)
				for (vector<Entity*>::iterator it = GetEntityManager()->GetEntities().begin(); it != GetEntityManager()->GetEntities().end(); ++it)
					ShowEntity(**it);
			else
				for (vector<Entity*>::reverse_iterator it = GetEntityManager()->GetEntities().rbegin(); it != GetEntityManager()->GetEntities().rend(); ++it)
					ShowEntity(**it);
		}

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
}


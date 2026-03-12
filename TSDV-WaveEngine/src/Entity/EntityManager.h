#pragma once

#include "ServiceProvider/Service.h"

#include <map>
#include <list>
#include <unordered_map>
#include <typeindex>
#include <concepts>
#include <vector>

#include "Entity/Entity.h"
#include "Material/MaterialManager.h"

#include "EventSystem/Event.h"

class BaseGame;
class EntityFactory;

using namespace std;

namespace WaveEngine
{
	template<typename T>
	concept EntityManagerStandar = derived_from<T, Entity>;

	template<typename T>
	concept EntityManagerGetStandar = derived_from<T, Entity> || derived_from<T, Drawable>;

	struct EntityChangeLayer : public Event
	{
		unsigned int ID = 0;
		int oldLayer = 0;
		int newLayer = 0;

		EntityChangeLayer(const unsigned int& ID, const int& oldLayer, const int& newLayer)
		{
			this->ID = ID;
			this->oldLayer = oldLayer;
			this->newLayer = newLayer;
		}

		EntityChangeLayer()
		{
		}

		void Reset() override
		{
			ID = 0;
			oldLayer = 0;
			newLayer = 0;
		}
	};

	class EntityManager final : public Service
	{
	private:

		map<unsigned int, Entity*> entitiesByID;
		map<unsigned int, Drawable*> drawableByID;

		unordered_map<type_index, vector<unsigned int>> entitiesIDByType;

		map<int, list<unsigned int>> drawableByLayer;

		ServiceProvider* serviceProvider;
		MaterialManager* materialManager;

		inline void SaveEntity(const unsigned int& ID, Entity* entity);

		inline void DrawEntities();

		inline EntityManager(ServiceProvider* serviceProvider, MaterialManager* materialManager);
		inline ~EntityManager();

		inline void OnEntityChangeLayer(const EntityChangeLayer& entityChangeLayer);
		inline void OnEntityDestroy(const unsigned int& id);

		inline map<unsigned int, Drawable*>& GetDrawables();

		friend class Entity;
		friend class EntitiesImGui;
		friend class MeshImGui;
		friend class Drawable;
		friend class ServiceProvider;
		friend class EntityFactory;
		friend class BaseGame;

	public:

		inline map<unsigned int, Entity*>& GetEntities();

		template<EntityManagerGetStandar T>
		T* TryGet(const unsigned int& ID);

		inline Entity* TryGet(const unsigned int& ID);

		template<EntityManagerGetStandar T>
		T* Get(const unsigned int& ID);

		inline Entity* Get(const unsigned int& ID);

		template<EntityManagerGetStandar T>
		vector<unsigned int>& GetAllOfType();

		inline void DeleteEntity(const unsigned int& ID);

		template<EntityManagerGetStandar T>
		void DeleteAllOfType();

		inline void DeleteAll();
	};
}
#include "EntityManager.tpp"
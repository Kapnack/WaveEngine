#pragma once

#include "ServiceProvider/Service.h"

#include <map>
#include <list>
#include <unordered_map>
#include <typeindex>
#include <concepts>
#include <vector>

#include "Entity/Entity.h"
#include "Entity/Drawable/Drawable.h"
#include "Entity/Events/EntityChangeLayer.h"
#include "Material/MaterialManager.h"
#include "Material/Event/MaterialDelition.h"

class BaseGame;
class EntityFactory;

using namespace std;

namespace WaveEngine
{
	template<typename T>
	concept EntityManagerStandar = derived_from<T, Entity>;

	template<typename T>
	concept EntityManagerGetStandar = derived_from<T, Entity> || derived_from<T, Drawable>;

	class EntityManager final : public Service
	{
	private:

		vector<Entity*> entities;
		map<unsigned int, unsigned int> entitiesIndexByID;

		vector<Drawable*> drawables;
		map<unsigned int, unsigned int> drawableIndexByID;

		unordered_map<type_index, vector<unsigned int>> entitiesIDByType;

		map<int, vector<unsigned int>> drawableIDByLayer;

		ServiceProvider* serviceProvider;

		inline void SaveEntity(const unsigned int& ID, Entity* entity);

		inline void DrawEntities();

		inline EntityManager(ServiceProvider* serviceProvider);
		inline ~EntityManager();

		inline void OnEntityChangeLayer(const EntityChangeLayer& entityChangeLayer);
		inline void OnEntityDestroy(const unsigned int& ID);

		inline vector<Drawable*>& GetDrawables();

		inline void OnMaterialDeleted(const MaterialDelition& materialDelition);

		friend class Entity;
		friend class EntitiesImGui;
		friend class MeshImGui;
		friend class Drawable;
		friend class ServiceProvider;
		friend class EntityFactory;
		friend class BaseGame;

	public:

		inline vector<Entity*>& GetEntities();

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
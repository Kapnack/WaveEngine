#pragma once

#include "ServiceProvider/Service.h"

#include <map>
#include <typeindex>

#include "Entity.h"

#include <concepts>
#include <vector>

#include "Entity/Drawable/Drawable.h"
#include "Material/MaterialManager.h"

class BaseGame;
class EntityFactory;

using namespace std;

template<typename T>
concept EntityManagerStandar = derived_from<T, Entity>;

template<typename T>
concept EntityManagerGetStandar = derived_from<T, Entity> || derived_from<T, Drawable>;

class EntityManager final : public Service
{
private:

	map<unsigned int, Entity*> entitiesByID;
	map<unsigned int, Drawable*> drawableByID;

	unordered_map<type_index, vector<unsigned int>> entitiesIDByType;

	map<int, list<unsigned int>> drawableByLayer;

	MaterialManager* materialManager;

	inline void SaveEntity(const unsigned int& ID, Entity* entity);

	inline void DrawEntities();

	inline EntityManager(MaterialManager* materialManager);
	inline ~EntityManager();

	inline void OnEntityChangeLayer(const unsigned int& id, const int& oldLayer, const int& newLayer);
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

#include "EntityManager.tpp"
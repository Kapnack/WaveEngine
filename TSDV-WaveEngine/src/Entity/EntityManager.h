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

class EntityManager final : public Service
{
private:

	map<unsigned int, Entity*> entitiesByID;
	map<unsigned int, Drawable*> drawableByID;

	unordered_map<type_index, vector<unsigned int>> entitiesIDByType;

	map<int, list<unsigned int>> entityByLayer;

	template<EntityManagerStandar T>
	void SaveEntity(const unsigned int& ID, T* entity);

	inline void DrawEntities();

	inline EntityManager();
	inline ~EntityManager();

	inline void OnEntityChangeLayer(const unsigned int& id, const int& oldLayer, const int& newLayer);
	inline void OnEntityDestroy(const unsigned int& id);

	friend class Entity;
	friend class EntitiesImGui;
	friend class MeshImGui;
	friend class Drawable;
	friend class ServiceProvider;
	friend class EntityFactory;
	friend class BaseGame;

public:

	inline map<unsigned int, Entity*>& GetEntities();

	template<EntityManagerStandar T>
	T* TryGet(const unsigned int& ID);

	inline Entity* TryGet(const unsigned int& ID);

	template<EntityManagerStandar T>
	T* Get(const unsigned int& ID);

	inline Entity* Get(const unsigned int& ID);

	template<EntityManagerStandar T>
	vector<unsigned int>& GetAllOfType();

	inline void DeleteEntity(const unsigned int& ID);

	template<EntityManagerStandar T>
	void DeleteAllOfType();

	inline void DeleteAll();
};

#include "EntityManager.tpp"
#pragma once

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"

#include <unordered_map>
#include <typeindex>

#include "Entity.h"

#include <concepts>
#include <vector>

#include "Export.h"

class BaseGame;
class EntityFactory;

using namespace std;

template<typename T>
concept EntityManagerStandar = is_base_of_v<Entity, T>;

class EntityManager final : public Service
{
private:

	unordered_map<unsigned int, Entity*> entitiesByID;

	unordered_map<type_index, vector<unsigned int>> entitiesIDByType;

	template<EntityManagerStandar T>
	void SaveEntity(const unsigned int& ID, T* entity);

	inline void DrawEntities();

	inline EntityManager();
	inline ~EntityManager();

	friend class ServiceProvider;
	friend class EntityFactory;
	friend class BaseGame;

public:

	template<EntityManagerStandar T>
	T* Get(const unsigned int& ID);

	inline Entity* Get(const unsigned int& ID);

	template<EntityManagerStandar T>
	vector<T*> GetAll();
};

#include "EntityManager.tpp"
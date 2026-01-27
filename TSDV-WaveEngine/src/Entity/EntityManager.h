#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <typeindex>

#include "Entity.h"

#include <concepts>
#include <vector>

#include "Material/MaterialManager.h"

class BaseGame;
class EntityFactory;

using namespace std;

template<typename T>
concept EntityManagerStandar = derived_from<T, Entity>;

class EntityManager final : public Service
{
private:

	MaterialManager* materialManager;

	unordered_map<unsigned int, Entity*> entitiesByID;

	unordered_map<type_index, vector<unsigned int>> entitiesIDByType;


	template<EntityManagerStandar T>
	void SaveEntity(const unsigned int& ID, T* entity);

	inline void DrawEntities();

	inline EntityManager(MaterialManager* materialManager);
	inline ~EntityManager();

	friend class ServiceProvider;
	friend class EntityFactory;
	friend class BaseGame;

public:

	inline unordered_map<unsigned int, Entity*>& GetEntities();

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
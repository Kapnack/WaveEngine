#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include "EntityManager.h"
#include "TileMap/Tile.h"

EntityManager::EntityManager() : Service()
{
}

EntityManager::~EntityManager()
{
	for (unordered_map<const unsigned int, Entity*>::iterator service = entitiesByID.begin(); service != entitiesByID.end(); ++service)
		delete service->second;

	entitiesByID.clear();
	entitiesIDByType.clear();
}

inline void EntityManager::DrawEntities()
{
	for (unordered_map<const unsigned int, Entity*>::iterator service = entitiesByID.begin(); service != entitiesByID.end(); ++service)
		service->second->Draw();
}

template<EntityManagerStandar T>
void EntityManager::SaveEntity(const unsigned int& ID, T* entity)
{
	entitiesByID[ID] = entity;
	entitiesIDByType[typeid(T)].push_back(ID);
}

template<EntityManagerStandar T>
T* EntityManager::Get(const unsigned int& ID)
{
	auto it = entitiesByID.find(ID);
	if (it == entitiesByID.end())
		return nullptr;

	return dynamic_cast<T*>(it->second);
}

Entity* EntityManager::Get(const unsigned int& ID)
{
	auto it = entitiesByID.find(ID);
	if (it == entitiesByID.end())
		return nullptr;

	return dynamic_cast<Entity*>(it->second);
}

template<EntityManagerStandar T>
vector<T*> EntityManager::GetAllOfType()
{
	vector<T*> entitiesOfType;

	for (vector<unsigned int>::iterator it = entitiesIDByType[typeid(T)].begin(); it != entitiesIDByType[typeid(T)].end(); it++)
		entitiesOfType.push_back(Get<T>(*it));

	return entitiesOfType;
}

#endif
#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include "EntityManager.h"

#include "TileMap/Tile.h"

EntityManager::EntityManager(MaterialManager* materialManager) : Service()
{
	this->materialManager = materialManager;
}

EntityManager::~EntityManager()
{
	for (unordered_map<const unsigned int, Entity*>::iterator service = entitiesByID.begin(); service != entitiesByID.end(); ++service)
		delete service->second;

	entitiesByID.clear();
	entitiesIDByType.clear();
}

unordered_map<unsigned int, Entity*>& EntityManager::GetEntities()
{
	return entitiesByID;
}

inline void EntityManager::DrawEntities()
{
	Tile* tile = nullptr;
	for (unordered_map<const unsigned int, Entity*>::iterator service = entitiesByID.begin(); service != entitiesByID.end(); ++service)
		if (tile = dynamic_cast<Tile*>(service->second))
			continue;
		else
			service->second->Draw();
}

template<EntityManagerStandar T>
void EntityManager::SaveEntity(const unsigned int& ID, T* entity)
{
	entitiesByID[ID] = entity;
	entitiesIDByType[typeid(*entity)].push_back(ID);
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
	return Get<Entity>(ID);
}

inline void EntityManager::DeleteEntity(const unsigned int& ID)
{
	delete entitiesByID[ID];
	entitiesByID.erase(ID);

	for (auto& [type, ids] : entitiesIDByType)
		ids.erase(remove(ids.begin(), ids.end(), ID), ids.end());
}

inline void EntityManager::DeleteAll()
{
	for (unordered_map<unsigned int, Entity*>::iterator it = entitiesByID.begin(); it != entitiesByID.end(); ++it)
		delete it->second;

	entitiesByID.clear();
	entitiesIDByType.clear();
}

template<EntityManagerStandar T>
vector<unsigned int>& EntityManager::GetAllOfType()
{
	return entitiesIDByType[typeid(T)];
}


template<EntityManagerStandar T>
void EntityManager::DeleteAllOfType()
{
	for (unsigned int& ID : entitiesIDByType[typeid(T)])
		DeleteEntity(ID);
}

#endif
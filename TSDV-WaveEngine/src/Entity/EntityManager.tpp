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
	for (map<const unsigned int, Entity*>::iterator service = entitiesByID.begin(); service != entitiesByID.end(); ++service)
		delete service->second;

	entitiesByID.clear();
	entitiesIDByType.clear();
}

void EntityManager::OnEntityChangeLayer(const unsigned int& id, const int& oldLayer, const int& newLayer)
{
	entityByLayer[oldLayer].remove(id);
	entityByLayer[newLayer].push_back(id);
}

inline void EntityManager::OnEntityDestroy(const unsigned int& id)
{
	for (map<int, list<unsigned int>>::iterator layer = entityByLayer.begin(); layer != entityByLayer.end(); ++layer)
		layer->second.remove(id);
}

map<unsigned int, Entity*>& EntityManager::GetEntities()
{
	return entitiesByID;
}

inline void EntityManager::DrawEntities()
{
	Tile* tile = nullptr;
	for (map<const unsigned int, Entity*>::iterator service = entitiesByID.begin(); service != entitiesByID.end(); ++service)
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
	map<unsigned int, Entity*>::iterator it = entitiesByID.find(ID);
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
	OnEntityDestroy(ID);
	delete entitiesByID[ID];
	entitiesByID.erase(ID);

	for (unordered_map<type_index, vector<unsigned int>>::iterator it = entitiesIDByType.begin(); it != entitiesIDByType.end(); ++it)
		it->second.erase(remove(it->second.begin(), it->second.end(), ID), it->second.end());
}

inline void EntityManager::DeleteAll()
{
	for (map<unsigned int, Entity*>::iterator it = entitiesByID.begin(); it != entitiesByID.end(); ++it)
		delete it->second;

	entitiesByID.clear();
	entitiesIDByType.clear();
	entityByLayer.clear();
}

template<EntityManagerStandar T>
vector<unsigned int>& EntityManager::GetAllOfType()
{
	return entitiesIDByType[typeid(T)];
}


template<EntityManagerStandar T>
void EntityManager::DeleteAllOfType()
{
	for (unsigned int id : entitiesIDByType[typeid(T)])
	{
		map<unsigned int, Entity*>::iterator it = entitiesByID.find(id);
		if (it != entitiesByID.end())
		{
			OnEntityDestroy(it->first);
			delete it->second;
			entitiesByID.erase(it);
		}
	}

	entitiesIDByType[typeid(T)].clear();
}

#endif
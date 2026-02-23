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
	DeleteAll();
}

void EntityManager::OnEntityChangeLayer(const unsigned int& id, const int& oldLayer, const int& newLayer)
{
	drawableByLayer[oldLayer].remove(id);
	drawableByLayer[newLayer].push_back(id);
}

inline void EntityManager::OnEntityDestroy(const unsigned int& id)
{
	for (map<int, list<unsigned int>>::iterator layer = drawableByLayer.begin(); layer != drawableByLayer.end(); ++layer)
		layer->second.remove(id);

	if (!drawableByID.contains(id))
		return;

	if (drawableByID[id])
		materialManager->RemoveListener(drawableByID[id]);

	drawableByID.erase(id);
}

inline map<unsigned int, Drawable*>& EntityManager::GetDrawables()
{
	return drawableByID;
}

map<unsigned int, Entity*>& EntityManager::GetEntities()
{
	return entitiesByID;
}

inline void EntityManager::DrawEntities()
{
	for (map<int, list<unsigned int>>::iterator layer = drawableByLayer.begin(); layer != drawableByLayer.end(); ++layer)
		for (unsigned int entityID : layer->second)
			drawableByID.at(entityID)->Draw();
}

void EntityManager::SaveEntity(const unsigned int& ID, Entity* entity)
{
	entitiesByID[ID] = entity;

	entitiesIDByType[typeid(*entity)].push_back(ID);

	if (Drawable* drawable = dynamic_cast<Drawable*>(entity))
	{
		drawableByID[ID] = drawable;
		drawableByLayer[drawable->GetLayer()].push_back(ID);
		materialManager->AddListener(drawable);

		entitiesIDByType[typeid(Drawable)].push_back(ID);
	}
}

template<EntityManagerGetStandar T>
T* EntityManager::TryGet(const unsigned int& ID)
{
	if (ID == Entity::NULL_ENTITY)
		return nullptr;

	map<unsigned int, Entity*>::iterator it = entitiesByID.find(ID);
	if (it == entitiesByID.end())
		return nullptr;

	return dynamic_cast<T*>(it->second);
}

Entity* EntityManager::TryGet(const unsigned int& ID)
{
	return TryGet<Entity>(ID);
}

template<EntityManagerGetStandar T>
T* EntityManager::Get(const unsigned int& ID)
{
	return static_cast<T*>(entitiesByID.at(ID));
}

Entity* EntityManager::Get(const unsigned int& ID)
{
	return Get<Entity>(ID);
}

inline void EntityManager::DeleteEntity(const unsigned int& ID)
{
	if (ID == Entity::NULL_ENTITY || !entitiesByID.contains(ID))
		return;

	OnEntityDestroy(ID);

	delete entitiesByID[ID];
	entitiesByID.erase(ID);

	for (unordered_map<type_index, vector<unsigned int>>::iterator it = entitiesIDByType.begin(); it != entitiesIDByType.end(); ++it)
		it->second.erase(remove(it->second.begin(), it->second.end(), ID), it->second.end());
}

inline void EntityManager::DeleteAll()
{
	for (map<unsigned int, Entity*>::iterator it = entitiesByID.begin(); it != entitiesByID.end(); ++it)
	{
		OnEntityDestroy(it->first);
		delete it->second;
	}

	entitiesByID.clear();
	entitiesIDByType.clear();
	drawableByLayer.clear();
}

template<EntityManagerGetStandar T>
vector<unsigned int>& EntityManager::GetAllOfType()
{
	return entitiesIDByType[typeid(T)];
}


template<EntityManagerGetStandar T>
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
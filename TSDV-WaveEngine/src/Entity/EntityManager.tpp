#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include "EntityManager.h"

#include "EventSystem/EventSystem.h"
#include "Material/MaterialManager.h"

namespace WaveEngine
{
	EntityManager::EntityManager(ServiceProvider* serviceProvider) : Service()
	{
		this->serviceProvider = serviceProvider;

		serviceProvider->Get<EventSystem>()->Subscribe<EntityChangeLayer>(this, &EntityManager::OnEntityChangeLayer);
		serviceProvider->Get<EventSystem>()->Subscribe<MaterialDelition>(this, &EntityManager::OnMaterialDeleted);
	}

	EntityManager::~EntityManager()
	{
		DeleteAll();

		serviceProvider->Get<EventSystem>()->Unsubscribe<EntityChangeLayer>(this, &EntityManager::OnEntityChangeLayer);
		serviceProvider->Get<EventSystem>()->Unsubscribe<MaterialDelition>(this, &EntityManager::OnMaterialDeleted);
	}

	void EntityManager::OnEntityChangeLayer(const EntityChangeLayer& entityChangeLayer)
	{
		drawableByLayer[entityChangeLayer.oldLayer].remove(entityChangeLayer.ID);
		drawableByLayer[entityChangeLayer.newLayer].push_back(entityChangeLayer.ID);
	}

	inline void EntityManager::OnEntityDestroy(const unsigned int& id)
	{
		for (map<int, list<unsigned int>>::iterator layer = drawableByLayer.begin(); layer != drawableByLayer.end(); ++layer)
			layer->second.remove(id);

		if (!drawableByID.contains(id))
			return;

		drawableByID.erase(id);
	}

	inline map<unsigned int, Drawable*>& EntityManager::GetDrawables()
	{
		return drawableByID;
	}

	inline void EntityManager::OnMaterialDeleted(const MaterialDelition& materialDelition)
	{
		for (map<unsigned int, Drawable*>::iterator it = drawableByID.begin(); it != drawableByID.end(); ++it)
			if (it->second->GetMaterial() == materialDelition.ID)
				it->second->SetMaterial(Material::NULL_MATERIAL);
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
}
#endif
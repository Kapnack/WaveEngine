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
		//drawableIDByLayer[entityChangeLayer.oldLayer].erase(drawableIDByLayer[entityChangeLayer.oldLayer].begin() + entityChangeLayer.ID);
		//drawableIDByLayer[entityChangeLayer.newLayer].push_back(entityChangeLayer.ID);
	}

	inline void EntityManager::OnEntityDestroy(const unsigned int& ID)
	{
		auto it = drawableIndexByID.find(ID);
		if (it == drawableIndexByID.end())
			return;

		unsigned int index = it->second;
		unsigned int lastIndex = drawables.size() - 1;

		Drawable* lastDrawable = drawables[lastIndex];

		std::swap(drawables[index], drawables[lastIndex]);

		drawableIndexByID[lastDrawable->GetID()] = index;

		drawables.pop_back();
		drawableIndexByID.erase(ID);

	}

	inline vector<Drawable*>& EntityManager::GetDrawables()
	{
		return drawables;
	}

	inline void EntityManager::OnMaterialDeleted(const MaterialDelition& materialDelition)
	{
		for (vector<Drawable*>::iterator it = drawables.begin(); it != drawables.end(); ++it)
			if ((*it)->GetMaterial() == materialDelition.ID)
				(*it)->SetMaterial(Material::NULL_MATERIAL);
	}

	vector<Entity*>& EntityManager::GetEntities()
	{
		return entities;
	}

	inline void EntityManager::DrawEntities()
	{
		for (Drawable* d : drawables)
			d->Draw();
	}

	void EntityManager::SaveEntity(const unsigned int& ID, Entity* entity)
	{
		entities.push_back(entity);
		entitiesIndexByID[ID] = entities.size() - 1;

		entitiesIDByType[typeid(*entity)].push_back(ID);

		if (Drawable* drawable = dynamic_cast<Drawable*>(entity))
		{
			drawables.push_back(drawable);
			drawableIndexByID[ID] = drawables.size() - 1;
			drawableIDByLayer[drawable->GetLayer()].push_back(ID);
			entitiesIDByType[typeid(Drawable)].push_back(ID);
		}
	}

	template<EntityManagerGetStandar T>
	T* EntityManager::TryGet(const unsigned int& ID)
	{
		if (ID == Entity::NULL_ENTITY)
			return nullptr;

		map<unsigned int, unsigned int>::iterator it = entitiesIndexByID.find(ID);
		if (it == entitiesIndexByID.end())
			return nullptr;

		return dynamic_cast<T*>(entities.at(it->second));
	}

	Entity* EntityManager::TryGet(const unsigned int& ID)
	{
		return TryGet<Entity>(ID);
	}

	template<EntityManagerGetStandar T>
	T* EntityManager::Get(const unsigned int& ID)
	{
		return static_cast<T*>(entities.at(entitiesIndexByID.at(ID)));
	}

	Entity* EntityManager::Get(const unsigned int& ID)
	{
		return Get<Entity>(ID);
	}

	inline void EntityManager::DeleteEntity(const unsigned int& ID)
	{
		if (ID == Entity::NULL_ENTITY)
			return;

		auto it = entitiesIndexByID.find(ID);
		if (it == entitiesIndexByID.end())
			return;

		unsigned int index = it->second;
		unsigned int lastIndex = entities.size() - 1;

		Entity* entity = entities[index];
		Entity* lastEntity = entities[lastIndex];

		OnEntityDestroy(ID);

		swap(entities[index], entities[lastIndex]);

		entitiesIndexByID[lastEntity->GetID()] = index;

		entities.pop_back();
		entitiesIndexByID.erase(ID);

		delete entity;

		type_index entityType = typeid(*entity);

		entitiesIDByType.at(entityType).erase(remove(entitiesIDByType.at(entityType).begin(), entitiesIDByType.at(entityType).end(), ID), entitiesIDByType.at(entityType).begin());
	}

	inline void EntityManager::DeleteAll()
	{
		for (Entity* e : entities)
		{
			if (!e)
				continue;

			delete e;
		}

		entities.clear();
		drawables.clear();

		entitiesIndexByID.clear();
		drawableIndexByID.clear();

		entitiesIDByType.clear();
		drawableIDByLayer.clear();
	}

	template<EntityManagerGetStandar T>
	vector<unsigned int>& EntityManager::GetAllOfType()
	{
		return entitiesIDByType[typeid(T)];
	}


	template<EntityManagerGetStandar T>
	void EntityManager::DeleteAllOfType()
	{
		auto& ids = entitiesIDByType[typeid(T)];

		std::vector<unsigned int> copy = ids;

		for (unsigned int id : copy)
			DeleteEntity(id);

		ids.clear();
	}
}
#endif
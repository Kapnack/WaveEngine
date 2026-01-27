#ifndef ENTITYFACTORY
#define ENTITYFACTORY

#include "EntityFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include"Entity/EntityManager.h"

#include "Entity/Entity2D/Sprite/Sprite.h"

EntityFactory::EntityFactory(EntityManager* entityManager, MaterialManager* materialManager, Window* window) : Service()
{
	this->entityManager = entityManager;
	this->materialManager = materialManager;
	this->window = window;
}

EntityFactory::~EntityFactory()
{
}

template<EntityManagerStandar T>
unsigned int EntityFactory::Create()
{
	++currentEntityID;

	T* newEntity = new T(currentEntityID);

	Entity* newEntityAsEntity = newEntity;

	newEntityAsEntity->SetPosition(window->GetBaseWidth() * 0.5, window->GetBaseHeight() * 0.5);
	newEntityAsEntity->SetScale(window->GetBaseWidth() * 0.5, window->GetBaseHeight() * 0.5);

	entityManager->SaveEntity(currentEntityID, newEntityAsEntity);

	materialManager->AddListener(newEntityAsEntity);

	return currentEntityID;
}


#endif
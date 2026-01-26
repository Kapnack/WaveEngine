#ifndef ENTITYFACTORY
#define ENTITYFACTORY

#include "EntityFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include"Entity/EntityManager.h"

#include "Entity/Entity2D/Sprite/Sprite.h"

EntityFactory::EntityFactory(EntityManager* entityManager, MaterialManager* materialManager) : Service()
{
	this->entityManager = entityManager;
	this->materialManager = materialManager;
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

	entityManager->SaveEntity(currentEntityID, newEntityAsEntity);

	materialManager->AddListener(newEntityAsEntity);

	return currentEntityID;
}


#endif
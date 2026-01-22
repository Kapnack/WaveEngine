#ifndef ENTITYFACTORY
#define ENTITYFACTORY

#include "EntityFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include"Entity/EntityManager.h"

EntityFactory::EntityFactory(EntityManager* entityManager) : Service()
{
	this->entityManager = entityManager;
}

EntityFactory::~EntityFactory()
{
}

template<EntityManagerStandar T>
unsigned int EntityFactory::Create()
{
	T* newEntity = new T();

	++currentEntityID;
	newEntity->ID = currentEntityID;

	entityManager->SaveEntity(currentEntityID, newEntity);

	return currentEntityID;
}


#endif
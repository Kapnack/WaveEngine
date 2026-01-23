#ifndef ENTITYFACTORY
#define ENTITYFACTORY

#include "EntityFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include"Entity/EntityManager.h"

#include "Entity/Entity2D/Sprite/Sprite.h"

EntityFactory::EntityFactory(EntityManager* entityManager, ImGuiClass* imGuiClass, MaterialManager* materialManager) : Service()
{
	this->entityManager = entityManager;
	this->imGuiClass = imGuiClass;
	this->materialManager = materialManager;
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
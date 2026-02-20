#ifndef ENTITYFACTORY
#define ENTITYFACTORY

#include "EntityFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include"Entity/EntityManager.h"

#include "Entity/Entity2D/Sprite/Sprite.h"

#include "TileMap/TileMap.h"

EntityFactory::EntityFactory(EntityManager* entityManager, Window* window) : Service()
{
	this->entityManager = entityManager;
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

	entityManager->SaveEntity(currentEntityID, newEntity);

	return currentEntityID;
}

unsigned int EntityFactory::CreateTileMap(const string& mapFilePath, const bool& mapFileAddAbsolutePath, const string& texturePath, const bool& texturePathAddAbsolutePath)
{
	++currentEntityID;

	TileMap* newEntity = new TileMap(mapFilePath, mapFileAddAbsolutePath, texturePath, texturePathAddAbsolutePath, currentEntityID);

	entityManager->SaveEntity(newEntity->GetID(), newEntity);

	newEntity->SetScale(Vector3::One());

	newEntity->ImportTileMap(mapFilePath, mapFileAddAbsolutePath);

	return currentEntityID;
}

#endif
#pragma once

#include "Entity/EntityManager.h"
#include "ServiceProvider/Service.h"
#include "Material/MaterialManager.h"
#include "ServiceProvider/ServiceProvider.h"

#include "Export.h"

class BaseGame;

 class EntityFactory final : public Service
{
private:

	EntityManager* entityManager;
	MaterialManager* materialManager;

	unsigned int currentEntityID = Entity::NULL_ENTITY;

	inline EntityFactory(EntityManager* entityManager, MaterialManager* materialManager);
	inline ~EntityFactory();

	friend class ServiceProvider;
	friend class BaseGame;

public:

	template<EntityManagerStandar T>
	 unsigned int Create();
};

#include "EntityFactory.tpp"

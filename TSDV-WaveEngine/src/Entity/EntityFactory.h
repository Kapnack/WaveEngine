#pragma once

#include "Entity/EntityManager.h"
#include "ServiceProvider/Service.h"
#include "ImGuiClass/ImGuiClass.h"
#include "Material/MaterialManager.h"
#include "ServiceProvider/ServiceProvider.h"

#include "Export.h"

class BaseGame;

 class EntityFactory final : public Service
{
private:

	EntityManager* entityManager;
	ImGuiClass* imGuiClass;
	MaterialManager* materialManager;

	unsigned int currentEntityID = Entity::NULL_ENTITY;

	inline EntityFactory(EntityManager* entityManager, ImGuiClass* imGuiClass, MaterialManager* materialManager);
	inline ~EntityFactory();

	friend class ServiceProvider;
	friend class BaseGame;

public:

	template<EntityManagerStandar T>
	 unsigned int Create();
};

#include "EntityFactory.tpp"

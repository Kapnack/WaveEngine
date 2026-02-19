#pragma once

#include "Entity/EntityManager.h"
#include "ServiceProvider/Service.h"
#include "Window/Window.h"
#include "Material/MaterialManager.h"
#include "ServiceProvider/ServiceProvider.h"

#include "Export.h"

class BaseGame;

class EntityFactory final : public Service
{
private:

	EntityManager* entityManager;
	MaterialManager* materialManager;
	Window* window;

	unsigned int currentEntityID = Entity::NULL_ENTITY;

	inline EntityFactory(EntityManager* entityManager, MaterialManager* materialManager, Window* window);
	inline ~EntityFactory();

	friend class ServiceProvider;
	friend class BaseGame;

public:

	template<EntityManagerStandar T>
	unsigned int Create();

	inline unsigned int CreateTileMap(const string& mapFilePath, const bool& mapFileAddAbsolutePath, const string& texturePath, const bool& texturePathAddAbsolutePath);
};

#include "EntityFactory.tpp"

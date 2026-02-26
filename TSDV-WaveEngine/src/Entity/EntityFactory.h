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
	Window* window;

	unsigned int currentEntityID = Entity::NULL_ENTITY;

	inline EntityFactory(EntityManager* entityManager, Window* window);
	inline ~EntityFactory();

	friend class ServiceProvider;
	friend class BaseGame;

public:

	template<EntityManagerStandar T>
	unsigned int Create();

	inline unsigned int CreateTileMap(const string_view mapFilePath, const bool& mapFileAddAbsolutePath, const string_view texturePath, const bool& texturePathAddAbsolutePath);
};

#include "EntityFactory.tpp"

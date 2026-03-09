#pragma once

#include "ServiceProvider/Service.h"
#include "Serializable/Serializable.h"

#include "Entity/EntityManager.h"
#include "Window/Window.h"
#include "Material/MaterialManager.h"
#include "ServiceProvider/ServiceProvider.h"

#include "Export.h"

namespace WaveEngine
{
	class BaseGame;

	class EntityFactory final : public Service, public Serializable
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

		void Serialize(std::ostream& stream) const override;
		void Deserialize(std::istream& stream) override;
	};
}
#include "EntityFactory.tpp"

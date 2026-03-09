#ifndef ENTITYFACTORY
#define ENTITYFACTORY

#include "EntityFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include"Entity/EntityManager.h"

#include "Entity/Entity2D/Sprite/Sprite.h"

#include "TileMap/TileMap.h"

namespace WaveEngine
{
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

	unsigned int EntityFactory::CreateTileMap(const string_view mapFilePath, const bool& mapFileAddAbsolutePath, const string_view texturePath, const bool& texturePathAddAbsolutePath)
	{
		++currentEntityID;

		TileMap* newEntity = new TileMap(mapFilePath, mapFileAddAbsolutePath, texturePath, texturePathAddAbsolutePath, currentEntityID);

		entityManager->SaveEntity(newEntity->GetID(), newEntity);

		newEntity->SetScale(Vector3::One());

		newEntity->ImportTileMap(mapFilePath, mapFileAddAbsolutePath);

		return newEntity->GetID();
	}

	void EntityFactory::Serialize(std::ostream& stream) const
	{
		size_t typeCount = entityManager->entitiesIDByType.size();
		stream.write((char*)&typeCount, sizeof(typeCount));

		for (const auto& pair : entityManager->entitiesIDByType)
		{
			const std::type_index& type = pair.first;
			const std::vector<unsigned int>& ids = pair.second;

			std::string name = type.name();
			size_t len = name.size();

			stream.write((char*)&len, sizeof(len));
			stream.write(name.data(), len);

			size_t idCount = ids.size();
			stream.write((char*)&idCount, sizeof(idCount));

			for (unsigned int id : ids)
			{
				Entity* entity = entityManager->entitiesByID.at(id);

				stream.write((char*)&id, sizeof(id));
				entity->Serialize(stream);
			}
		}
	}

	void EntityFactory::Deserialize(std::istream& stream)
	{
		size_t typeCount;
		stream.read((char*)&typeCount, sizeof(typeCount));

		for (size_t i = 0; i < typeCount; i++)
		{
			size_t len;
			stream.read((char*)&len, sizeof(len));

			std::string typeName(len, '\0');
			stream.read(typeName.data(), len);

			size_t idCount;
			stream.read((char*)&idCount, sizeof(idCount));

			for (size_t j = 0; j < idCount; j++)
			{
				unsigned int id;
				stream.read((char*)&id, sizeof(id));

				Entity* entity = CreateEntityFromType(typeName);
				entity->Deserialize(stream);

				entityManager->entitiesByID[id] = entity;
			}
		}
	}
}
#endif
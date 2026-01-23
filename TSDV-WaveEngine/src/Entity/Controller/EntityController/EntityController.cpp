#include "EntityController.h"

EntityController::EntityController() : Controller()
{
}

EntityController::EntityController(const unsigned int entityID) : Controller(entityID)
{
}

EntityController::~EntityController()
{
}

void EntityController::Update(const float& deltaTime)
{
	Entity* entity;

	for (vector<unsigned int>::iterator it = entitiesIDs.begin(); it != entitiesIDs.end(); ++it)
	{
		entity = GetEntityManager()->Get<Entity>(*it);

		if (entity == nullptr)
			continue;

		if (GetInput()->IsKeyPressed(Keys::W))
			entity->Translate(Vector3::Up() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::S))
			entity->Translate(Vector3::Down() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::A))
			entity->Translate(Vector3::Left() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::D))
			entity->Translate(Vector3::Right() * deltaTime * 100);
	}
}

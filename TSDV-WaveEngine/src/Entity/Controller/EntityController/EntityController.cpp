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
	for (vector<unsigned int>::iterator it = entitiesIDs.begin(); it != entitiesIDs.end(); ++it)
	{
		currentEntity = GetEntityManager()->TryGet(*it);

		if (!currentEntity)
			continue;

		if (GetInput()->IsKeyPressed(Keys::W))
			currentEntity->Translate(Vector3::Up() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::S))
			currentEntity->Translate(Vector3::Down() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::A))
			currentEntity->Translate(Vector3::Left() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::D))
			currentEntity->Translate(Vector3::Right() * deltaTime * 100);
	}
}
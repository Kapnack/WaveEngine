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
		if (!GetEntityManager()->TryGet(*it))
			continue;

		if (GetInput()->IsKeyPressed(Keys::W))
			GetEntityManager()->Get(*it)->Translate(Vector3::Up() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::S))
			GetEntityManager()->Get(*it)->Translate(Vector3::Down() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::A))
			GetEntityManager()->Get(*it)->Translate(Vector3::Left() * deltaTime * 100);

		if (GetInput()->IsKeyPressed(Keys::D))
			GetEntityManager()->Get(*it)->Translate(Vector3::Right() * deltaTime * 100);
	}
}
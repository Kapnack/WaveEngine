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

Entity* EntityController::GetEntity()
{
	return GetEntityManager()->Get<Entity>(GetEntityID());
}


void EntityController::Update(const float& deltaTime)
{
	if (GetInput()->IsKeyPressed(Keys::W))
		GetEntity()->Translate(Vector3::Up() * deltaTime * 100);

	if (GetInput()->IsKeyPressed(Keys::S))
		GetEntity()->Translate(Vector3::Down() * deltaTime * 100);

	if (GetInput()->IsKeyPressed(Keys::A))
		GetEntity()->Translate(Vector3::Left() * deltaTime * 100);

	if (GetInput()->IsKeyPressed(Keys::D))
		GetEntity()->Translate(Vector3::Right() * deltaTime * 100);
}

#include "CollisionManager.h"
#include "Collider.h"

bool CollisionManager::CheckCollision(Entity2D* anEntity, Entity2D* otherEntity)
{
    Collider entityCollider = anEntity->GetCollider();
    Collider otherCollider = otherEntity->GetCollider();

	return entityCollider.x < otherCollider.x + otherCollider.width &&
        entityCollider.x + entityCollider.width > otherCollider.x &&
        entityCollider.y < otherCollider.y + otherCollider.height &&
        entityCollider.y + entityCollider.height > otherCollider.y;
}

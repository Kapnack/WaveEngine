#include "CollisionManager.h"
#include "Collider.h"

bool CollisionManager::CheckCollision(const Entity2D& anEntity, const Entity2D& otherEntity) const noexcept
{

	Collider entityCollider = anEntity.GetCollider();
	Collider otherCollider = otherEntity.GetCollider();

	return entityCollider.x < otherCollider.x + otherCollider.width &&
		entityCollider.x + entityCollider.width > otherCollider.x &&
		entityCollider.y < otherCollider.y + otherCollider.height &&
		entityCollider.y + entityCollider.height > otherCollider.y;
}

bool CollisionManager::CheckCollision(const Entity2D& entity, const TileMap& tileMap) const
{
    return false;
}

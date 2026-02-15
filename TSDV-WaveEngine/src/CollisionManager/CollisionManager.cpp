#include "CollisionManager.h"
#include "Collider.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Entity/EntityManager.h"

CollisionManager::CollisionManager() : Service()
{
}

CollisionManager::~CollisionManager()
{
}

EntityManager* CollisionManager::GetEntityManager() const
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

bool CollisionManager::AreColliding(const Collider& a, const Collider& b) const
{
	return a.x < b.x + b.width &&
		a.x + a.width > b.x &&
		a.y < b.y + b.height &&
		a.y + a.height > b.y;
}

bool CollisionManager::CheckCollision(const unsigned int& anEntity, const unsigned int& otherEntity) const
{
	if (!GetEntityManager()->TryGet<Entity2D>(anEntity) || !GetEntityManager()->TryGet<Entity2D>(otherEntity))
		return false;

	if (!GetEntityManager()->Get<Entity2D>(anEntity)->GetIsActive() || !GetEntityManager()->Get<Entity2D>(otherEntity)->GetIsActive())
		return false;

	Collider entityCollider = GetEntityManager()->Get<Entity2D>(anEntity)->GetCollider();
	Collider otherCollider = GetEntityManager()->Get<Entity2D>(otherEntity)->GetCollider();

	return AreColliding(entityCollider, otherCollider);
}

bool CollisionManager::CheckCollision(const unsigned int& entityID, const TileMap& tileMap) const
{
	if (!GetEntityManager()->TryGet<Entity2D>(entityID))
		return false;
	
	if (!GetEntityManager()->Get<Entity2D>(entityID)->GetIsActive())
		return false;

	Collider entityCollider = GetEntityManager()->Get<Entity2D>(entityID)->GetCollider();

	const float tileW = tileMap.GetTileWidth();
	const float tileH = tileMap.GetTileHeight();

	const int mapW = tileMap.GetMapWidth();
	const int mapH = tileMap.GetMapHeight();

	if (tileW == 0 || tileH == 0 || mapH == 0 || mapW == 0)
		return false;

	const float windowH = tileMap.GetMapHeight() * tileH;

	const float left = entityCollider.x;
	const float right = entityCollider.x + entityCollider.width;
	const float bottom = entityCollider.y;
	const float top = entityCollider.y + entityCollider.height;

	int leftTile = int(floor(left / tileW));
	int rightTile = int(floor((right - 0.001f) / tileW));

	int topTile = int(floor((windowH - bottom) / tileH));
	int bottomTile = int(floor((windowH - top) / tileH));

	leftTile = clamp(leftTile, 0, mapW - 1);
	rightTile = clamp(rightTile, 0, mapW - 1);
	topTile = clamp(topTile, 0, mapH - 1);
	bottomTile = clamp(bottomTile, 0, mapH - 1);

	for (int row = bottomTile; row <= topTile; ++row)
	{
		for (int col = leftTile; col <= rightTile; ++col)
		{
			for (int layer = 0; layer < tileMap.GetLayerCount(); ++layer)
			{
				unsigned int tileID = tileMap.GetTileAt(layer, row, col);

				if (tileID == Entity::NULL_ENTITY)
					continue;

				if (!GetEntityManager()->TryGet<Tile>(tileID))
					continue;

				if (!GetEntityManager()->Get<Tile>(tileID)->CanCollide())
					continue;

				Collider tileCollider = GetEntityManager()->Get<Tile>(tileID)->GetCollider();

				if (AreColliding(entityCollider, tileCollider))
					return true;
			}
		}
	}

	return false;
}
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

bool CollisionManager::CheckCollision(const unsigned int& anEntity, const unsigned int& otherEntity) const
{
	Entity* entityA = ServiceProvider::Instance().Get<EntityManager>()->Get<Entity>(otherEntity);
	Entity* entityB = ServiceProvider::Instance().Get<EntityManager>()->Get<Entity>(otherEntity);

	if (!entityA || !entityB)
		return false;

	Entity2D* entity2Da = dynamic_cast<Entity2D*>(entityA);
	Entity2D* entity2Db = dynamic_cast<Entity2D*>(entityB);

	if (!entity2Da || !entity2Db)
		return false;

	Collider entityCollider = entity2Da->GetCollider();
	Collider otherCollider = entity2Db->GetCollider();

	return entityCollider.x < otherCollider.x + otherCollider.width &&
		entityCollider.x + entityCollider.width > otherCollider.x &&
		entityCollider.y < otherCollider.y + otherCollider.height &&
		entityCollider.y + entityCollider.height > otherCollider.y;
}

bool CollisionManager::CheckCollision(const Entity2D& entity, const TileMap& tileMap) const
{
	Collider c = entity.GetCollider();

	const float tileW = tileMap.GetTileWidth();
	const float tileH = tileMap.GetTileHeight();

	const int mapW = tileMap.GetMapWidth();
	const int mapH = tileMap.GetMapHeight();

	const float windowH = tileMap.GetMapHeight() * tileH;

	const float left = c.x;
	const float right = c.x + c.width;
	const float bottom = c.y;
	const float top = c.y + c.height;

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

				Entity2D* tile = ServiceProvider::Instance().Get<EntityManager>()->Get<Tile>(tileID);

				if (!tile)
					continue;

				if (!ServiceProvider::Instance().Get<EntityManager>()->Get<Tile>(tileID)->CanCollide())
					continue;

				unsigned int entityID = entity.GetID();

				if (CheckCollision(entityID, tileID))
					return true;
			}
		}
	}

	return false;
}
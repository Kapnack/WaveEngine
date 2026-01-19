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
    Collider c = entity.GetCollider();

    float tileW = tileMap.GetTileWidth();
    float tileH = tileMap.GetTileHeight();

    int mapW = tileMap.GetMapWidth();
    int mapH = tileMap.GetMapHeight();

    float windowH = tileMap.GetMapHeight() * tileH;

    float left = c.x;
    float right = c.x + c.width;
    float bottom = c.y;
    float top = c.y + c.height;

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
                Tile* tile = tileMap.GetTileAt(layer, row, col);

                if (!tile || !tile->CanCollide())
                    continue;

                if (CheckCollision(entity, *tile))
                    return true;
            }
        }
    }

    return false;
}

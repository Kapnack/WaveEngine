#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"
#include "Entity/Entity2D/Entity2D.h"
#include "TileMap/TileMap.h"

WAVEEXPORT class CollisionManager : public Service
{
public:

	WAVEEXPORT CollisionManager();
	WAVEEXPORT ~CollisionManager();

	WAVEEXPORT bool CheckCollision(const unsigned int& anEntity, const unsigned int& otherEntity) const;
	WAVEEXPORT bool CheckCollision(const Entity2D& anEntity, const TileMap& tileMap) const;
};


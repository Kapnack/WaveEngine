#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"
#include "Entity/Entity2D/Entity2D.h"
#include "TileMap/TileMap.h"

#include "ServiceProvider/ServiceProvider.h"

WAVEEXPORT class CollisionManager : public Service
{
public:
	WAVEEXPORT bool CheckCollision(const Entity2D& anEntity, const Entity2D& otherEntity) const noexcept;
	WAVEEXPORT bool CheckCollision(const Entity2D& anEntity, const TileMap& tileMap) const;
};


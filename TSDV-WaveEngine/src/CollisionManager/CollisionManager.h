#pragma once

#include "Export.h"
#include "Entity/Entity2D/Entity2D.h"

WAVEEXPORT class CollisionManager
{
public:
	WAVEEXPORT static bool CheckCollision(Entity2D* anEntity, Entity2D* otherEntity);
};


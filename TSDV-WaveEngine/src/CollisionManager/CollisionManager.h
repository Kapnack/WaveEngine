#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"
#include "Entity/Entity2D/Entity2D.h"
#include "TileMap/TileMap.h"

class BaseGame;
class ServiceProvider;

WAVEEXPORT class CollisionManager : public Service
{
private:

	CollisionManager();
	~CollisionManager();

	friend class BaseGame;
	friend class ServiceProvider;

public:


	WAVEEXPORT bool CheckCollision(const unsigned int& anEntity, const unsigned int& otherEntity) const;
	WAVEEXPORT bool CheckCollision(const Entity2D* anEntity, const TileMap& tileMap) const;
};


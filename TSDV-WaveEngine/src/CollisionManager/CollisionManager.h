#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"
#include "Entity/Entity2D/Entity2D.h"
#include "TileMap/TileMap.h"
#include "Entity/EntityManager.h"
#include "Collider.h"

class BaseGame;
class ServiceProvider;

WAVEEXPORT class CollisionManager : public Service
{
private:

	EntityManager* GetEntityManager() const;

	bool AreColliding(const Collider& a, const Collider& b) const;

	CollisionManager();
	~CollisionManager();

	friend class BaseGame;
	friend class ServiceProvider;

public:


	WAVEEXPORT bool CheckCollision(const unsigned int& anEntity, const unsigned int& otherEntity) const;
	WAVEEXPORT bool CheckCollision(const unsigned int& anEntity, const TileMap& tileMap) const;
};


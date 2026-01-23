#pragma once

#include "Entity/Entity.h"
#include "CollisionManager/Collider.h"

WAVEEXPORT class Entity2D : public Entity
{
protected:

	Collider collider;
	void UpdateCollider() override;

public:

	WAVEEXPORT Entity2D(const unsigned int& ID);
	WAVEEXPORT virtual ~Entity2D();

	WAVEEXPORT Collider GetCollider() const;
};
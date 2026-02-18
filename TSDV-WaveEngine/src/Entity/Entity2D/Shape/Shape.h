#pragma once

#include "Entity/Entity2D/Entity2D.h"
#include "Entity/Drawable/Drawable.h"

class EntityFactory;
class EntityManager;

WAVEEXPORT class Shape : public Entity2D, public Drawable
{
protected:

	WAVEEXPORT void Draw() override;

	WAVEEXPORT Shape(const unsigned int& ID);
	WAVEEXPORT virtual ~Shape();

	friend class EntityFactory;
	friend class EntityManager;
};


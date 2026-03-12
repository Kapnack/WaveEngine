#pragma once

#include "Entity/Entity.h"
#include "Entity/Drawable/Drawable.h"

namespace WaveEngine
{
	class Entity3D : public Entity, public Drawable
	{
	private:

	public:

		Entity3D(const unsigned int& ID);
		virtual ~Entity3D();
	};
}


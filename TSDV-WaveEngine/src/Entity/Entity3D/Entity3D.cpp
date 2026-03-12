#include "Entity3D.h"

namespace WaveEngine
{
	Entity3D::Entity3D(const unsigned int& ID) : Entity(ID), Drawable(ID)
	{
	}

	Entity3D::~Entity3D()
	{
	}
}

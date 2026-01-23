#include "Entity2D.h"

Entity2D::Entity2D(const unsigned int& ID) : Entity(ID)
{
	UpdateCollider();
}

Entity2D::~Entity2D()
{
}

Collider Entity2D::GetCollider() const
{
	return collider;
}

void Entity2D::UpdateCollider()
{
	collider =
	{
		position.x - scale.x * 0.5f,
		position.y - scale.y * 0.5f,
		scale.x,
		scale.y
	};
}

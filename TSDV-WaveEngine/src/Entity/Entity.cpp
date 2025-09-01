#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Entity::SetPosition(Vector3 vector)
{
	position = vector;
}
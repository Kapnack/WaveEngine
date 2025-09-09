#include "Entity.h"

Entity::Entity(Renderer* renderer, Vector3 position)
{
	this->renderer = renderer;
	this->position = position;
}

Entity::~Entity()
{
	delete vertex;
	delete indices;
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

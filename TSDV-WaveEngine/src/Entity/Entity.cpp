#include "Entity.h"

Entity::Entity(Renderer* renderer)
{
	this->renderer = renderer;

	SetTRS();
}

Entity::~Entity()
{
	delete vertex;
	delete indices;
}

Vector3 Entity::GetScale()
{
	return scale;
}

Vector3 Entity::GetPosition()
{
	return position;
}

void Entity::SetPosition(Vector3 vector)
{
	SetPosition(vector.x, vector.y);
}

void Entity::SetPosition(float x, float y)
{
	position.x = x; /// renderer->GetRes().x;
	position.y = y; /// renderer->GetRes().y;

	SetTRS();
}

void Entity::Translate(Vector3 translation)
{
	Translate(translation.x, translation.y);
}

void Entity::Translate(float x, float y)
{
	position.x += x;
	position.y += y;

	SetTRS();
}

void Entity::SetScale(Vector3 vector)
{
	SetScale(vector.x, vector.y);
}

void Entity::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;

	SetTRS();
}

void Entity::Scale(Vector3 vector)
{
	Scale(vector.x, vector.y);
}

void Entity::Scale(float x, float y)
{
	scale.x += x;
	scale.y += y;
	
	SetTRS();
}

void Entity::SetRotation(float angle)
{
	rotation = angle;

	SetTRS();
}

void Entity::Rotate(float angle)
{
	rotation += angle;

	SetTRS();
}

void Entity::SetTRS()
{
	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z)); // Translate
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z)); // Scale
}

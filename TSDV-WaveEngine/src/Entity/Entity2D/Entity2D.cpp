#include "Entity2D.h"

Entity2D::Entity2D() : Entity()
{
	UpdateCollider();
}

Entity2D::~Entity2D()
{
}

void Entity2D::UpdateCollider()
{
	collider =
	{
		position.x,
		position.y,
		scale.x,
		scale.y
	};
}

Collider Entity2D::GetCollider()
{
	return collider;
}

Vector3 Entity2D::GetPosition()
{
	return position;
}

Vector3 Entity2D::GetScale()
{
	return scale;
}

void Entity2D::SetPosition(Vector3 vector)
{
	SetPosition(vector.x, vector.y);
}

void Entity2D::SetPosition(float x, float y)
{
	previousPosition = position;

	position.x = x;
	position.y = y;

	SetTRS();
	UpdateCollider();
}

float Entity2D::GetRotation()
{
	return rotation;
}

void Entity2D::Translate(Vector3 translation)
{
	Translate(translation.x, translation.y);
}

void Entity2D::Translate(float x, float y)
{
	previousPosition = position;

	position.x += x;
	position.y += y;

	SetTRS();
	UpdateCollider();
}

void Entity2D::SetScale(Vector3 vector)
{
	SetScale(vector.x, vector.y);
}

void Entity2D::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;

	SetTRS();
	UpdateCollider();
}

void Entity2D::Scale(Vector3 vector)
{
	Scale(vector.x, vector.y);
}

void Entity2D::Scale(float x, float y)
{
	scale.x += x;
	scale.y += y;

	SetTRS();
	UpdateCollider();
}

void Entity2D::SetRotation(float angle)
{
	rotation = angle;
	SetTRS();
}

void Entity2D::Rotate(float angle)
{
	rotation += angle;
	SetTRS();
}

void Entity2D::SetColor(Vector4 color)
{
	for (int i = 0; i < vertexSize; i++)
		vertex[i].SetColor(color);

	GetRenderer()->UpdateBuffer(vertex, vertexSize, VBO);
}

void Entity2D::SetVertexColor(int index, Vector4 color)
{
	if (index < 0 || index >= vertexSize)
		return;

	vertex[index].SetColor(color);
	GetRenderer()->UpdateBuffer(vertex, vertexSize, VBO);
}
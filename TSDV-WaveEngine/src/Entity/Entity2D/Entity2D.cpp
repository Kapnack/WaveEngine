#include "Entity2D.h"

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

Entity2D::Entity2D(Renderer* renderer) : Entity(renderer)
{
}

Entity2D::~Entity2D()
{
}

Collider Entity2D::GetCollider()
{
	return collider;
}

Vector3 Entity2D::GetPos()
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
	position.x = x;
	position.y = y;

	translation.x = x;
	translation.y = y;

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
	{
		vertex[i].SetColor(color);
	}

	renderer->UpdateBuffer(vertex, vertexSize, VBO);
}

void Entity2D::SetVertexColor(int index, Vector4 color)
{
	if (index < 0 || index > indexSize)
	{
		cout << "ERROR: Index is: " + to_string(index) + ". and it should be between 0 to " + to_string(indexSize) + ".";
		return;
	}

	vertex[index].SetColor(color);
	renderer->UpdateBuffer(vertex, vertexSize, VBO);
}

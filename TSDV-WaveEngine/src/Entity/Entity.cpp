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

Vector3 Entity::GetPos()
{
	return position;
}

Vector3 Entity::GetScale()
{
	return scale;
}

void Entity::SetPosition(Vector3 vector)
{
	SetPosition(vector.x, vector.y);
}

void Entity::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	SetTRS();
}

float Entity::GetRotation()
{
	return rotation;
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

void Entity::SetColor(Vector4 color)
{
	for (int i = 0; i < vertexSize; i++)
	{
		vertex[i].SetColor(color);
	}

	renderer->UpdateBuffer(vertex, vertexSize, VBO);
}

void Entity::SetVertexColor(int index, Vector4 color)
{
	if (index < 0 || index > indexSize)
	{
		cout << "ERROR: Index is: " + to_string(index) + ". and it should be between 0 to " + to_string(indexSize) + ".";
		return;
	}

	vertex[index].SetColor(color);
	renderer->UpdateBuffer(vertex, vertexSize, VBO);
}

void Entity::SetTRS()
{
	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z)); // Translate
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z)); // Scale
}

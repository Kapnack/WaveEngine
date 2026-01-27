#include "Entity.h"

#include "Material/MaterialManager.h"
#include "ImGuiClass/ImGuiClass.h"
#include "Entity/EntityManager.h"

Entity::Entity(const unsigned int& ID)
{
	this->ID = ID;

	SetTRS();
}

Entity::~Entity()
{
	delete[] vertex;
	delete[] indices;
}

unsigned int Entity::GetID() const
{
	return ID;
}

void Entity::SetIsActive(const bool& setActive)
{
	isActive = setActive;
}

bool Entity::GetIsActive()
{
	return isActive;
}

void Entity::SetMaterial(const unsigned int materialID)
{
	this->materialID = materialID;
}

const unsigned int Entity::GetMaterial() const
{
	return materialID;
}

Vector3 Entity::GetPosition() const
{
	return position;
}

Vector3 Entity::GetScale() const
{
	return scale;
}

Vector3 Entity::GetRotation() const
{
	return rotation;
}

Vector3 Entity::GetPreviousPos() const
{
	return previousPosition;
}

void Entity::GoToPreviousPos()
{
	SetPosition(previousPosition);
}

void Entity::SetPosition(const Vector3& vector)
{
	SetPosition(vector.x, vector.y, vector.z);
}

void Entity::SetPosition(const Vector2& translation)
{
	SetPosition(translation.x, translation.y);
}

void Entity::SetPosition(const float& x, const float& y)
{
	SetPosition(x, y, position.z);
}

void Entity::SetPosition(const float& x, const float& y, const float& z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	previousPosition = position;

	SetTRS();

	UpdateCollider();
}

void Entity::Translate(const Vector3& translation)
{
	Translate(translation.x, translation.y, translation.z);
}

void Entity::Translate(const Vector2& translation)
{
	Translate(translation.x, translation.y);
}

void Entity::Translate(const float& x, const float& y)
{
	Translate(x, y, 0);
}

void Entity::Translate(const float& x, const float& y, const float& z)
{
	previousPosition = position;

	position.x += x;
	position.y += y;
	position.z += z;

	SetTRS();

	UpdateCollider();
}

void Entity::SetScale(const Vector3& vector)
{
	SetScale(vector.x, vector.y, vector.z);
}

void Entity::SetScale(const Vector2& translation)
{
	SetScale(translation.x, translation.y);
}

void Entity::SetScale(const float& x, const float& y)
{
	SetScale(x, y, scale.z);
}

void Entity::SetScale(const float& x, const float& y, const float& z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;

	SetTRS();

	UpdateCollider();
}

void Entity::Scale(const Vector3& vector)
{
	Scale(vector.x, vector.y, vector.z);
}

void Entity::Scale(const Vector2& translation)
{
	Scale(translation.x, translation.y);
}

void Entity::Scale(const float& x, const float& y)
{
	Scale(x, y, 0);
}

void Entity::Scale(const float& x, const float& y, const float& z)
{
	scale.x += x;
	scale.y += y;
	scale.z += z;

	SetTRS();

	UpdateCollider();
}

void Entity::SetRotation(const Vector3& vector)
{
	SetRotation(vector.x, vector.y, vector.z);
}

void Entity::SetRotation(const Vector2& vector)
{
	SetRotation(vector.x, vector.y);
}

void Entity::SetRotation(const float& x, const float& y)
{
	SetRotation(x, y, rotation.z);
}

void Entity::SetRotation(const float& x, const float& y, const float& z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;

	SetTRS();

	UpdateCollider();
}

void Entity::Rotate(const Vector3& vector)
{
	Rotate(vector.x, vector.y, vector.z);
}

void Entity::Rotate(const Vector2& vector)
{
	Rotate(vector.x, vector.y);
}

void Entity::Rotate(const float& x, const float& y)
{
	Rotate(x, y, 0);
}

void Entity::Rotate(const float& x, const float& y, const float& z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;

	SetTRS();

	UpdateCollider();
}

void Entity::SetColor(const Vector4& color)
{
	for (int i = 0; i < vertexSize; i++)
		vertex[i].SetColor(color);

	UpdateVertexBuffer();
}

void Entity::SetVertexColor(const int& index, const Vector4& color)
{
	if (index < 0 || index >= vertexSize)
		return;

	vertex[index].SetColor(color);
	UpdateVertexBuffer();
}

void Entity::FlipX()
{
	SetScale(-scale.x, scale.y, scale.z);
}

void Entity::FlipY()
{
	SetScale(scale.x, -scale.y, scale.z);
}

void Entity::FlipZ()
{
	SetScale(scale.x, scale.y, -scale.z);
}

void Entity::UpdateVertexBuffer()
{
	GetRenderer()->UpdateBuffer(vertex, vertexSize, VBO);
}

void Entity::SetTRS()
{
	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z)); // Translate
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));// Rotate X
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));// Rotate Y
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotate Z
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z)); // Scale
}

Renderer* Entity::GetRenderer() const
{
	return ServiceProvider::Instance().Get<Renderer>();
}
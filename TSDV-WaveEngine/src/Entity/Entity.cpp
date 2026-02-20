#include "Entity.h"

#include "Material/MaterialManager.h"
#include "ImGuiClass/ImGuiClass.h"
#include "Entity/EntityManager.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Entity/EntityManager.h"

Entity::Entity(const unsigned int& ID)
{
	this->ID = ID;
}

Entity::~Entity()
{
}

void Entity::Update()
{
	if (!isActive)
		return;
}

unsigned int Entity::GetID() const
{
	return ID;
}

void Entity::SetIsActive(const bool& setActive)
{
	isActive = setActive;
}

bool Entity::GetIsActive() const
{
	return isActive;
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

	UpdateCollider();

	SetUpdateTRS();
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

	UpdateCollider();

	SetUpdateTRS();
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

	UpdateCollider();

	SetUpdateTRS();
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

	UpdateCollider();

	SetUpdateTRS();
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

	UpdateCollider();

	SetUpdateTRS();
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

	UpdateCollider();

	SetUpdateTRS();
}

void Entity::SetParent(const unsigned int& parentID)
{
	if (this->parentID == parentID || parentID == ID)
		return;

	if (this->parentID != Entity::NULL_ENTITY)
		ServiceProvider::Instance().Get<EntityManager>()->Get(this->parentID)->RemoveChild(ID);

	this->parentID = parentID;

	if (parentID != Entity::NULL_ENTITY)
		ServiceProvider::Instance().Get<EntityManager>()->Get(parentID)->AddChild(ID);
}

unsigned int Entity::GetParent() const
{
	return parentID;
}

void Entity::AddChild(const unsigned int& childID)
{
	if (ContainsChild(childID))
		return;

	childsIDs.push_back(childID);

	ServiceProvider::Instance().Get<EntityManager>()->Get(childID)->SetParent(ID);
}

unsigned int Entity::GetChild(const unsigned int& index) const
{
	return childsIDs[index];
}

void Entity::RemoveChild(const unsigned int& childID)
{
	if (childID == Entity::NULL_ENTITY || !ContainsChild(childID))
		return;

	childsIDs.erase(remove(childsIDs.begin(), childsIDs.end(), childID));

	ServiceProvider::Instance().Get<EntityManager>()->Get(childID)->SetParent(Entity::NULL_ENTITY);
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

bool Entity::ContainsChild(const unsigned int& ID) const
{
	if (childsIDs.size() == 0)
		return false;

	for (vector<unsigned int>::const_iterator childID = childsIDs.begin(); childID != childsIDs.end(); ++childID)
		if (*childID == ID)
			return true;

	return false;
}

void Entity::SetUpdateTRS()
{
	shouldUpdateTRS = true;
}

void Entity::SetLocalFromMatrix(glm::mat4 matrix)
{
	glm::vec3 newPosition = glm::vec3(model[3]);

	position = Vector3(newPosition.x, newPosition.y, newPosition.z);

	scale.x = glm::length(glm::vec3(matrix[0]));
	scale.y = glm::length(glm::vec3(matrix[1]));
	scale.z = glm::length(glm::vec3(matrix[2]));

	if (scale.x == 0 || scale.y == 0 || scale.z == 0)
		return;

	glm::mat3 rotMat;
	rotMat[0] = glm::vec3(matrix[0]) / scale.x;
	rotMat[1] = glm::vec3(matrix[1]) / scale.y;
	rotMat[2] = glm::vec3(matrix[2]) / scale.z;

	glm::quat q = glm::quat_cast(rotMat);
	q = glm::normalize(q);

	glm::highp_vec3 newRot = glm::degrees(glm::eulerAngles(q));

	rotation = Vector3(newRot.x, newRot.y, newRot.z);
}

void Entity::UpdateTRS()
{
	if (!isActive || !shouldUpdateTRS)
		return;

	CalculateTRS();
}

void Entity::CalculateTRS()
{
	if (!isActive)
		return;

	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z)); // Translate
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));// Rotate X
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));// Rotate Y
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotate Z
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z)); // Scale

	if (parentID != Entity::NULL_ENTITY)
		model = ServiceProvider::Instance().Get<EntityManager>()->Get(parentID)->model * model;

	for (vector<unsigned int>::const_iterator childID = childsIDs.begin(); childID != childsIDs.end(); childID++)
		ServiceProvider::Instance().Get<EntityManager>()->Get(*childID)->CalculateTRS();
}
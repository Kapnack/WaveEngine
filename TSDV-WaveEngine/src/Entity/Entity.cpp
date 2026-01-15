#include "Entity.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialManager.h"

void Entity::SetTRS()
{
	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z)); // Translate
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z)); // Scale
}

Entity::Entity(Renderer* renderer)
{
	this->renderer = renderer;

	SetTRS();

	ServiceProvider::Instance().Get<MaterialManager>()->AddListener(this);
}

Entity::~Entity()
{
	delete vertex;
	delete indices;

	ServiceProvider::Instance().Get<MaterialManager>()->RemoveListener(this);
}

void Entity::SetMaterial(Material* material)
{
	this->material = material;
}

Material& Entity::GetMaterial()
{
	return *material;
}

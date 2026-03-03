#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include "ServiceProvider/ServiceProvider.h"

Camera Camera::camera;

Camera::Camera(const unsigned int& ID) : Entity(ID)
{
}

Camera::Camera() : Entity(Entity::NULL_ENTITY)
{
}

Camera::~Camera()
{
}

void Camera::UpdateCollider()
{
}

void Camera::CalculateTRS()
{
	Entity::CalculateTRS();

	CalculateMatrixes();
}

void Camera::SetOrthographic(const bool& value)
{
	orthografic = value;

	CalculateMatrixes();
}

void Camera::SetFarPlane(const float& value)
{
	farPlane = value;

	CalculateMatrixes();
}

void Camera::AddToFarPlane(const float& value)
{
	farPlane += value;

	CalculateMatrixes();
}

void Camera::SetNearPlane(const float& value)
{
	nearPlane = value;

	CalculateMatrixes();
}

void Camera::AddToNearPlane(const float& value)
{
	nearPlane += value;

	CalculateMatrixes();
}

void Camera::SetFovDegree(const float& value)
{
	fovDeg = value;

	CalculateMatrixes();
}

void Camera::SetOrthoSize(const float& value)
{
	orthoSize = value;
}

void Camera::AddToOrthoSize(const float& value)
{
	orthoSize += value;
}

glm::mat4 Camera::GetView()
{
	return view;
}

glm::mat4 Camera::GetProjection()
{
	return projection;
}

float Camera::GetFarPlane()
{
	return farPlane;
}

float Camera::GetNearPlane()
{
	return nearPlane;
}

float Camera::GetFovDegree()
{
	return fovDeg;
}

float Camera::GetMovementSpeed()
{
	return movementSpeed;
}

float Camera::GetOrthoSize()
{
	return orthoSize;
}

void Camera::CalculateMatrixes()
{
	float aspect =
		static_cast<float>(GetWindow()->GetWidth()) /
		static_cast<float>(GetWindow()->GetHeight());

	glm::vec3 pos = glm::vec3(position.x, position.y, position.z);

	glm::mat4 rotationMatrix = glm::yawPitchRoll
	(
		glm::radians(rotation.y),
		glm::radians(rotation.x),
		glm::radians(rotation.z)
	);

	glm::vec3 forward = glm::vec3(rotationMatrix * glm::vec4(0, 0, -1, 0));
	glm::vec3 up = glm::vec3(rotationMatrix * glm::vec4(0, 1, 0, 0));

	float halfHeight = orthoSize;
	float halfWidth = orthoSize * aspect;

	view = glm::lookAt(pos, pos + forward, up);

	projection = orthografic ?
		glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane)
		:
		glm::perspective(glm::radians(fovDeg), aspect, nearPlane, farPlane);
}

Window* Camera::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

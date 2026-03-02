#pragma once

#include "Entity/Entity.h"

#include <glm/mat4x4.hpp>

#include "Export.h"
#include "Window/Window.h"
#include "Vector3.h"

class EntityManager;
class EntityFactory;
class Renderer;

WAVEEXPORT class Camera : public Entity
{
private:

	float fovDeg = 45.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	float orthoSize = 500.0f;

	float movementSpeed = 100.0f;
	float sensitivity = 100.0f;

	bool orthografic = false;

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	void CalculateMatrixes();

	Window* GetWindow();

	Camera(const unsigned& ID);
	Camera();
	~Camera();

	glm::mat4 GetView();
	glm::mat4 GetProjection();

	friend class EntityManager;
	friend class EntityFactory;
	friend class Renderer;

protected:

	void UpdateCollider() override;
	void CalculateTRS() override;

public:

	static Camera camera;

	WAVEEXPORT void SetOrthographic(const bool& value);
	WAVEEXPORT void SetFarPlane(const float& value);
	WAVEEXPORT void AddToFarPlane(const float& value);
	WAVEEXPORT void SetNearPlane(const float& value);
	WAVEEXPORT void AddToNearPlane(const float& value);
	WAVEEXPORT void SetFovDegree(const float& value);
	WAVEEXPORT void SetOrthoSize(const float& value);
	WAVEEXPORT void AddToOrthoSize(const float& value);

	WAVEEXPORT float GetFarPlane();
	WAVEEXPORT float GetNearPlane();
	WAVEEXPORT float GetFovDegree();
	WAVEEXPORT float GetMovementSpeed();
	WAVEEXPORT float GetOrthoSize();
};
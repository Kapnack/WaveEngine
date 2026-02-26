#pragma once

#include "Export.h"
#include "Renderer/Renderer.h"
#include "VertexData.h"

class EntityFactory;
class EntityManager;
class EntitiesImGui;
class MeshImGui;

WAVEEXPORT class Entity
{
private:

	unsigned int ID = 0;

	bool isActive = true;
	bool shouldUpdateTRS = false;

	friend class EntityFactory;
	friend class EntityManager;
	friend class EntitiesImGui;
	friend class MeshImGui;

protected:

	Vector3 previousPosition;
	Vector3 position;

	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 rotation;

	glm::mat4 model;

	void CalculateTRS();

	virtual void UpdateCollider() = 0;

	WAVEEXPORT	Entity(const unsigned int& ID);
	WAVEEXPORT virtual ~Entity();

public:

	static const unsigned int NULL_ENTITY = 0;

	WAVEEXPORT unsigned int GetID() const;

	WAVEEXPORT void SetIsActive(const bool& setActive);
	WAVEEXPORT bool GetIsActive() const;

	WAVEEXPORT Vector3 GetPosition() const;
	WAVEEXPORT Vector3 GetScale() const;
	WAVEEXPORT Vector3 GetRotation() const;

	WAVEEXPORT Vector3 GetPreviousPos() const;
	WAVEEXPORT void GoToPreviousPos();

	WAVEEXPORT void SetPosition(const Vector3& vector);
	WAVEEXPORT void SetPosition(const Vector2& translation);
	WAVEEXPORT void SetPosition(const float& x, const float& y);
	WAVEEXPORT virtual void SetPosition(const float& x, const float& y, const float& z);

	WAVEEXPORT void Translate(const Vector3& translation);
	WAVEEXPORT void Translate(const Vector2& translation);
	WAVEEXPORT void Translate(const float& x, const float& y);
	WAVEEXPORT virtual void Translate(const float& x, const float& y, const float& z);

	WAVEEXPORT void SetScale(const Vector3& vector);
	WAVEEXPORT void SetScale(const Vector2& translation);
	WAVEEXPORT void SetScale(const float& x, const float& y);
	WAVEEXPORT virtual void SetScale(const float& x, const float& y, const float& z);

	WAVEEXPORT void Scale(const Vector3& vector);
	WAVEEXPORT void Scale(const Vector2& translation);
	WAVEEXPORT void Scale(const float& x, const float& y);
	WAVEEXPORT virtual void Scale(const float& x, const float& y, const float& z);

	WAVEEXPORT void SetRotation(const Vector3& vector);
	WAVEEXPORT void SetRotation(const Vector2& vector);
	WAVEEXPORT void SetRotation(const float& x, const float& y);
	WAVEEXPORT virtual void SetRotation(const float& x, const float& y, const float& z);

	WAVEEXPORT void Rotate(const Vector3& vector);
	WAVEEXPORT void Rotate(const Vector2& vector);
	WAVEEXPORT void Rotate(const float& x, const float& y);
	WAVEEXPORT virtual void Rotate(const float& x, const float& y, const float& z);

	WAVEEXPORT void FlipX();
	WAVEEXPORT void FlipY();
	WAVEEXPORT void FlipZ();
};

#pragma once

#include <vector>

#include "Export.h"
#include "Renderer/Renderer.h"
#include "ServiceProvider/ServiceProvider.h"
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

	friend class EntityFactory;
	friend class EntityManager;
	friend class EntitiesImGui;
	friend class MeshImGui;

	void UpdateVertexBuffer();

protected:

	unsigned int materialID;

	Vector3 previousPosition;
	Vector3 position;

	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 rotation;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int layer = 0;

	VertexData* vertex;
	int vertexSize;

	int* indices;
	int indexSize;

	glm::mat4 model;

	void SetTRS();

	virtual void UpdateCollider() = 0;

	Renderer* GetRenderer() const;

	WAVEEXPORT	Entity(const unsigned int& ID);
	WAVEEXPORT virtual ~Entity();

public:

	static const unsigned int NULL_ENTITY = 0;

	WAVEEXPORT unsigned int GetID() const;

	WAVEEXPORT void SetLayer(const int& layer);
	WAVEEXPORT int GetLayer() const;

	WAVEEXPORT void SetIsActive(const bool& setActive);
	WAVEEXPORT bool GetIsActive();

	WAVEEXPORT void SetMaterial(const unsigned int materialID);
	WAVEEXPORT const unsigned int GetMaterial() const;

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

	WAVEEXPORT void SetColor(const Vector4& color);
	WAVEEXPORT void SetVertexColor(const int& index, const Vector4& color);

	WAVEEXPORT void FlipX();
	WAVEEXPORT void FlipY();
	WAVEEXPORT void FlipZ();

	WAVEEXPORT virtual void Draw() = 0;
};

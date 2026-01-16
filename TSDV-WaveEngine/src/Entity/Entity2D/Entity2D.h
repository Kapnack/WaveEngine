#pragma once

#include "Entity/Entity.h"
#include "CollisionManager/Collider.h"

WAVEEXPORT class Entity2D : public Entity
{
protected:

	Collider collider;
	void UpdateCollider();

public:

	WAVEEXPORT Entity2D();
	WAVEEXPORT virtual ~Entity2D();
	WAVEEXPORT Collider GetCollider();

	WAVEEXPORT Vector3 GetPos() override;
	WAVEEXPORT  Vector3 GetScale() override;
	WAVEEXPORT  float GetRotation() override;

	WAVEEXPORT  void Translate(Vector3 translation) override;
	WAVEEXPORT  void Translate(float x, float y) override;

	WAVEEXPORT  void SetPosition(float x, float y) override;
	WAVEEXPORT  void SetPosition(Vector3 vector) override;

	WAVEEXPORT  void SetScale(float x, float y) override;
	WAVEEXPORT  void SetScale(Vector3 vector) override;

	WAVEEXPORT  void Scale(float x, float y) override;
	WAVEEXPORT  void Scale(Vector3 vector) override;

	WAVEEXPORT  void SetRotation(float angle) override;
	WAVEEXPORT  void Rotate(float angle) override;

	WAVEEXPORT  void SetColor(Vector4 color) override;
	WAVEEXPORT  void SetVertexColor(int index, Vector4 color) override;
};


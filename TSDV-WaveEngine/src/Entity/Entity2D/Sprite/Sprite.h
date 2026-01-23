#pragma once

#include "../Entity2D.h"
#include "Entity/Entity2D/Animation/Animation.h"

class EntityFactory;

class Sprite : public Entity2D
{
private:

	unsigned int textureID = 0;
	Animation* animation = nullptr;

	Vector2 UV;

	void Init(const Vector4& color);

	friend class EntityFactory;

public:

	WAVEEXPORT Sprite(const unsigned int& ID);
	WAVEEXPORT virtual ~Sprite();

	WAVEEXPORT void SetUVCordinates(const Vector2& cord1, const Vector2& cord2);
	WAVEEXPORT void SetAnimation(Animation* animation);
	WAVEEXPORT void Update();
	WAVEEXPORT void SetTexture(const unsigned int& textureID);

	WAVEEXPORT void Draw() override;
};


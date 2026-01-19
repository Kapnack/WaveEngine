#pragma once

#include "../Entity2D.h"
#include "Entity/Entity2D/Animation/Animation.h"

class Sprite : public Entity2D
{
private:

	unsigned int texture = 0;
	Animation* animation = nullptr;

	Vector2 UV;

	void Init(const unsigned int& texture, const Vector4& color);

public:

	WAVEEXPORT Sprite(const unsigned int& texture);
	WAVEEXPORT Sprite(const unsigned int& texture, const Vector4& color);
	WAVEEXPORT virtual ~Sprite();

	WAVEEXPORT void SetUVCordinates(const Vector2& cord1, const Vector2& cord2);
	WAVEEXPORT void SetAnimation(Animation* animation);
	WAVEEXPORT void Update();

	WAVEEXPORT void Draw() override;
};


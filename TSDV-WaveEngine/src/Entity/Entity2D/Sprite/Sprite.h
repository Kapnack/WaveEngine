#pragma once

#include "../Entity2D.h"
#include "Entity/Entity2D/Animation/Animation.h"

class Sprite : public Entity2D
{
private:

	unsigned int texture = 0;
	Animation* animation = nullptr;

	Vector2 UV;

public:

	WAVEEXPORT Sprite(unsigned int texture, Renderer* renderer);
	WAVEEXPORT Sprite(unsigned int texture, Vector4 color, Renderer* renderer);
	WAVEEXPORT ~Sprite();

	WAVEEXPORT void SetUVCordinates(Vector2 cord1, Vector2 cord2);
	WAVEEXPORT void SetAnimation(Animation* animation);
	WAVEEXPORT void Update();

	WAVEEXPORT void Draw() override;
};


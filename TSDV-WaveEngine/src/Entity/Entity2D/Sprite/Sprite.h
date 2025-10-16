#pragma once
#include "../Entity2D.h"

class Sprite : public Entity2D
{
private:

	unsigned int texture;

public:

	WAVEEXPORT Sprite(unsigned int texture, Renderer* renderer);
	WAVEEXPORT Sprite(unsigned int texture, Vector4 color, Renderer* renderer);
	WAVEEXPORT ~Sprite();

	WAVEEXPORT void Draw() override;
};


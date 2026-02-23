#pragma once

#include "Export.h"
#include "Vector2.h"

class Frame
{
public:

	Vector2 topLeft;
	Vector2 bottomRight;

	Frame()
	{}

	Frame(const Vector2& topLeft, const Vector2& bottomRight)
	{
		this->topLeft = topLeft;
		this->bottomRight = bottomRight;
	}
};

WAVEEXPORT class Animation
{
private:

	float currentTime = 0;
	float animationTime = 0;
	float frameTime = 0;
	int framesQuantity = 0;

public:

	Frame* frames;
	unsigned int currentFrame;

	WAVEEXPORT Animation(const Vector2& startCoords,
		const Vector2& frameArea,
		const Vector2& textureArea,
		const int& framesQuantity,
		const float& animationTime);

	WAVEEXPORT ~Animation();
	WAVEEXPORT void Update();
	WAVEEXPORT void NextFrame();
	void ResetTime();

	Frame GetCurrentFrame();
};
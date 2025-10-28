#pragma once
#include <vector>
#include "Export.h"


WAVEEXPORT struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2()
	{}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class Frame
{
public:

	Vector2 topLeft;
	Vector2 bottomRight;

	Frame()
	{}

	Frame(Vector2 topLeft, Vector2 bottomRight)
	{
		this->topLeft = topLeft;
		this->bottomRight = bottomRight;
	}
};

WAVEEXPORT class Animation
{
private:

	float currentTime;
	float animationTime;
	float frameTime;

public:

	std::vector<Frame> frames;
	unsigned int currentFrame;

	WAVEEXPORT Animation(Vector2 startCoords, Vector2 frameArea, Vector2 textureArea, int framesQuantity, float animationTime);
	WAVEEXPORT ~Animation();
	WAVEEXPORT void Update();
	WAVEEXPORT void NextFrame();
	void ResetTime();

	Frame GetCurrentFrame();
};
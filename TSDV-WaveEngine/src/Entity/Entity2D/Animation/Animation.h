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

	const static float DEFAULT_SPEED;

	float currentTime = 0;
	float animationTime = 0;
	float timePerFrame = 0;
	int framesQuantity = 0;
	float animationSpeed = DEFAULT_SPEED;

	Frame* frames = nullptr;

	unsigned int currentFrame = 0;

	bool paused = false;

	void KeepTimerInBounds();
	void SetCurrentFrame();
	void AddToTimer(const float& addition);

public:


	WAVEEXPORT Animation(const Vector2& startCoords,
		const Vector2& frameArea,
		const Vector2& textureArea,
		const int& framesQuantity,
		const float& animationTime);

	WAVEEXPORT ~Animation();
	WAVEEXPORT void Update();
	WAVEEXPORT void MoveToNextFrame();
	WAVEEXPORT void MoveToPreviousFrame();
	WAVEEXPORT void GoToFrame(const int& index);
	WAVEEXPORT void ResetTime();
	WAVEEXPORT void Pause(); 
	WAVEEXPORT void UnPause(); 
	WAVEEXPORT void SetPause(const bool& paused); 
	WAVEEXPORT void SwitchPauseState(); 
	WAVEEXPORT bool GetPause(); 

	WAVEEXPORT void SetSpeed(const float& speed);

	WAVEEXPORT Frame GetCurrentFrame() const;
	WAVEEXPORT Frame GetFrame(int index) const;
};
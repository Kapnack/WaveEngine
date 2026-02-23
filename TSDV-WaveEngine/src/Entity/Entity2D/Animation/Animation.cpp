#include "Animation.h"
#include "Time/Time.h"

#include "ServiceProvider/ServiceProvider.h"

Animation::Animation(
	const Vector2& startCoords,
	const Vector2& frameArea,
	const Vector2& textureArea,
	const int& framesQuantity,
	const float& animationTime
)
{
	this->currentFrame = 0;
	this->currentTime = 0.0f;
	this->animationTime = animationTime;
	this->framesQuantity = framesQuantity;

	float frameWidthFloat = frameArea.x;
	float frameHeightFloat = frameArea.y;
	float textureWidth = textureArea.x;
	float textureHeight = textureArea.y;

	Vector2 startUVCoords = 
	{
		startCoords.x / textureWidth,
		startCoords.y / textureHeight
	};

	frames = new Frame[framesQuantity];

	for (int i = 0; i < framesQuantity; i++)
	{
		Vector2 leftTopUVCoords =
		{
			startUVCoords.x + ((i * frameWidthFloat) / textureWidth),
			startUVCoords.y
		};

		Vector2 rightBottomUVCoords =
		{
			startUVCoords.x + frameWidthFloat / textureWidth + ((i * frameWidthFloat) / textureWidth),
			startUVCoords.y - (frameHeightFloat / textureHeight)
		};

		frames[i] = Frame(leftTopUVCoords, rightBottomUVCoords);
	}

	frameTime = animationTime / framesQuantity;
}

Animation::~Animation()
{
	delete[] frames;
}

Frame Animation::GetCurrentFrame()
{
	return frames[currentFrame];
}

void Animation::Update()
{
	currentTime += ServiceProvider::Instance().Get<Time>()->GetDeltaTime();

	while (currentTime >= animationTime)
		currentTime -= animationTime;

	currentFrame = static_cast<int>(currentTime / frameTime);
}

void Animation::NextFrame()
{
	this->currentFrame++;
	if (this->currentFrame >= framesQuantity)
	{
		this->currentFrame = 0;
	}
}

void Animation::ResetTime()
{
	currentTime = 0;
}
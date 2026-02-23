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

	float frameWidthFloat = static_cast<float>(frameArea.x);
	float frameHeightFloat = static_cast<float>(frameArea.y);
	float textureWidth = static_cast<float>(textureArea.x);
	float textureHeight = static_cast<float>(textureArea.y);

	Vector2 startUVCoords = {
		startCoords.x / textureWidth,
		startCoords.y / textureHeight
	};

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

		frames.push_back(Frame(leftTopUVCoords, rightBottomUVCoords));
	}

	frameTime = animationTime / framesQuantity;
}

Animation::~Animation()
{
	frames.clear();
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
	if (this->currentFrame >= this->frames.size())
	{
		this->currentFrame = 0;
	}
}

void Animation::ResetTime()
{
	this->currentTime = 0;
}
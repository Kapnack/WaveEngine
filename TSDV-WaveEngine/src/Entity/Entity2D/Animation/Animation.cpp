#include "Animation.h"
#include "Time/Time.h"

#include "ServiceProvider/ServiceProvider.h"

Animation::Animation(
	Vector2 startCoords,
	Vector2 frameArea,
	Vector2 textureArea,
	int framesQuantity,
	float animationTime
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

		this->frames.push_back(Frame(leftTopUVCoords, rightBottomUVCoords));
	}

	this->frameTime = this->animationTime / static_cast<float>(this->frames.size());
}

Animation::~Animation()
{
	frames.clear();
}

Frame Animation::GetCurrentFrame()
{
	return this->frames[this->currentFrame];
}

void Animation::Update()
{
	this->currentTime += ServiceProvider::Instance().Get<Time>()->GetDeltaTime();

	while (this->currentTime >= this->animationTime)
		this->currentTime -= this->animationTime;

	this->currentFrame = static_cast<int>(this->currentTime / this->frameTime);
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
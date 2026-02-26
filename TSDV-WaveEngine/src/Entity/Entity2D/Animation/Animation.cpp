#include "Animation.h"
#include "Time/Time.h"

#include "ServiceProvider/ServiceProvider.h"

const float Animation::DEFAULT_SPEED = 1;

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

	timePerFrame = animationTime / framesQuantity;
}

Animation::~Animation()
{
	delete[] frames;
}

void Animation::KeepTimerInBounds()
{
	while (currentTime >= animationTime)
		currentTime -= animationTime;
}

void Animation::SetCurrentFrame()
{
	currentFrame = static_cast<int>(currentTime / timePerFrame);
}

void Animation::AddToTimer(const float& addition)
{
	currentTime += addition;

	KeepTimerInBounds();

	SetCurrentFrame();
}

Frame Animation::GetCurrentFrame() const
{
	return frames[currentFrame];
}

Frame Animation::GetFrame(int index) const
{
	index = index % framesQuantity;
	return frames[index];
}

void Animation::Update()
{
	if (paused)
		return;

	AddToTimer(animationSpeed * ServiceProvider::Instance().Get<Time>()->GetDeltaTime());
}

void Animation::MoveToNextFrame()
{
	AddToTimer(timePerFrame);
}

void Animation::MoveToPreviousFrame()
{
	AddToTimer(-timePerFrame);
}

void Animation::GoToFrame(const int& index)
{
	ResetTime();

	for (int i = 0; i < index; ++i)
		AddToTimer(timePerFrame);
}

void Animation::ResetTime()
{
	currentTime = 0;
}

void Animation::Pause()
{
	paused = true;
}

void Animation::UnPause()
{
	paused = false;
}

void Animation::SetPause(const bool& paused)
{
	this->paused = paused;
}

void Animation::SwitchPauseState()
{
	paused = !paused;
}

bool Animation::GetPause()
{
	return paused;
}

void Animation::SetSpeed(const float& speed)
{
	animationSpeed = speed;
}

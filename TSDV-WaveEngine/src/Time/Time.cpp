#include "Time.h"

Time::Time() : Service()
{
}

Time::~Time()
{
}

Window* Time::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

void Time::UpdateDeltaTime()
{
	float actualTime = GetWindow()->GetGLTime();

	deltaTime = actualTime - lastTime * multiplier;

	lastTime = actualTime;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

void Time::SetTimeScale(const float& multiplier)
{
	this->multiplier = multiplier;
}

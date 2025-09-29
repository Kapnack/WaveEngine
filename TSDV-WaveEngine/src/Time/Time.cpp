#include "Time.h"

Time::Time(Window* window)
{
	this->window = window;
}

Time::~Time()
{
}

void Time::SetDeltaTime()
{
	float actualTime = window->GetGLTime();

	deltaTime = actualTime - lastTime;

	lastTime = actualTime;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

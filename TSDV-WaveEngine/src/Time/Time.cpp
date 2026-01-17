#include "Time.h"

#include "ServiceProvider/ServiceProvider.h"

Time::Time()
{
}

Time::~Time()
{
}

Window* Time::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

void Time::SetDeltaTime()
{
	float actualTime = GetWindow()->GetGLTime();

	deltaTime = actualTime - lastTime;

	lastTime = actualTime;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

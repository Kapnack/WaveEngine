#include "Time.h"

#include "Window/Window.h"

float Time::deltaTime = 0;
float Time::lastTime = 0;

void Time::SetDeltaTime()
{
	float actualTime = Window::GetGLTime();

	deltaTime = actualTime - lastTime;

	lastTime = actualTime;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

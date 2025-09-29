#pragma once

#include "Window/Window.h"

class Time
{
private:

	Window* window;
	float deltaTime;
	float lastTime;

public:

	Time(Window* window);
	~Time();


	void SetDeltaTime();
	float GetDeltaTime();
};


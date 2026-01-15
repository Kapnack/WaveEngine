#pragma once

#include "Window/Window.h"
#include "ServiceProvider/Service.h"

class Time : public Service
{
private:

	Window* window;
	float deltaTime = 0;
	float lastTime = 0;

public:

	Time(Window* window);
	~Time();

	void SetDeltaTime();
	float GetDeltaTime();
};


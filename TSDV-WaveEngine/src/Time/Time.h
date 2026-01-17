#pragma once

#include "Window/Window.h"
#include "ServiceProvider/Service.h"

class Time : public Service
{
private:

	float deltaTime = 0;
	float lastTime = 0;

	Window* GetWindow();

public:

	Time();
	~Time();

	void SetDeltaTime();
	float GetDeltaTime();
};


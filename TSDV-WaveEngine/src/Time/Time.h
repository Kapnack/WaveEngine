#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"
#include "Window/Window.h"

WAVEEXPORT class Time : public Service
{
private:

	float deltaTime = 0;
	float lastTime = 0;

	Window* GetWindow();

public:

	Time();
	~Time();

	void SetDeltaTime();
	WAVEEXPORT float GetDeltaTime();
};


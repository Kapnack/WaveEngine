#pragma once

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"

#include "Export.h"
#include "Window/Window.h"

class BaseGame;

WAVEEXPORT class Time : public Service
{
private:

	float deltaTime = 0;
	float lastTime = 0;

	float multiplier = 1;

	Window* GetWindow();

	Time();
	~Time();

	void UpdateDeltaTime();

	friend class BaseGame;
	friend class ServiceProvider;

public:

	WAVEEXPORT float GetDeltaTime();
	WAVEEXPORT void SetTimeScale(const float& multiplier);
};


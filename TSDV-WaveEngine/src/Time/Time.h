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

	Window* GetWindow();

	Time();
	~Time();

	friend class BaseGame;
	friend class ServiceProvider;

public:

	void SetDeltaTime();
	WAVEEXPORT float GetDeltaTime();
};


#pragma once

#include "Export.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Time/Time.h"

WAVEEXPORT class Engine
{
private:

	Window* window;
	Renderer* renderer;

	void InitEngine(int width, int height);
	void EndEngine();

protected:

	float width = 0.0f;
	float height = 0.0f;

	WAVEEXPORT	Renderer* GetRenderer();

	WAVEEXPORT	virtual void Init() = 0;
	WAVEEXPORT	virtual void Update() = 0;
	WAVEEXPORT	virtual void Unload() = 0;

	WAVEEXPORT float GetDeltaTime();

public:

	WAVEEXPORT	Engine(int width, int height);
	WAVEEXPORT	virtual ~Engine();

	WAVEEXPORT	void Run();
};


#pragma once

#include "Export.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Time/Time.h"
#include "Input/Input.h"
#include "Material/MaterialManager.h"

WAVEEXPORT class BaseGame
{
private:

	Window* window;

	void InitEngine(int width, int height);
	void EndEngine();

	Time* GetTime();

protected:

	float width = 0.0f;
	float height = 0.0f;

	WAVEEXPORT	Renderer* GetRenderer();

	WAVEEXPORT	virtual void Init() = 0;
	WAVEEXPORT	virtual void Update() = 0;
	WAVEEXPORT	virtual void Unload() = 0;

	WAVEEXPORT float GetDeltaTime();

	WAVEEXPORT Input* GetInput();

public:

	WAVEEXPORT	BaseGame(int width, int height);
	WAVEEXPORT	virtual ~BaseGame();

	WAVEEXPORT	void Run();
};


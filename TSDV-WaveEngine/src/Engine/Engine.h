#pragma once

#include "Export.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"

class Engine
{
private:

	Window* window;
	Renderer* renderer;

	void InitEngine(int width, int height);
	void EndEngine();

protected:

	Renderer* GetRenderer();

public:

	Engine(int width, int height);
	virtual ~Engine();

	void Loop();

	virtual void Init() = 0;
	virtual void Update();
	virtual void Unload() = 0;
};


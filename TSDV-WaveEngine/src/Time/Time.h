#pragma once

class Time
{
private:

	static float deltaTime;
	static float lastTime;

public:

	static void SetDeltaTime();
	static float GetDeltaTime();
};


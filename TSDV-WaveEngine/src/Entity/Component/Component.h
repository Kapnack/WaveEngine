#pragma once

#include "Input/Input.h"

#include "Export.h"

namespace WaveEngine
{
	class Entity;

	WAVEEXPORT class Component
	{
	private:

		Entity* entity;

		friend class Entity;

	protected:

		Entity& GetEntity();

		float GetDeltaTime();

		Input& GetInput();

	public:

		WAVEEXPORT Component();
		WAVEEXPORT ~Component();

		WAVEEXPORT virtual void Update() = 0;
	};
}
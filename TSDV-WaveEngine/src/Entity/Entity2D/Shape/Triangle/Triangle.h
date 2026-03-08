#pragma once

#include "../Shape.h"

namespace WaveEngine
{
	class EntityFactory;
	class EntityManager;

	WAVEEXPORT class Triangle : public Shape
	{
	private:

		WAVEEXPORT Triangle(const unsigned int& ID);
		WAVEEXPORT ~Triangle();

		friend class EntityFactory;
		friend class EntityManager;
	};
}
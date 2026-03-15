#pragma once

#include "../Shape.h"

namespace WaveEngine
{
	class EntityFactory;
	class EntityManager;

	WAVEEXPORT class Square : public Shape
	{
	protected:

		WAVEEXPORT Square(const unsigned int& ID);
		WAVEEXPORT ~Square();

		friend class EntityFactory;
		friend class EntityManager;
	};
}
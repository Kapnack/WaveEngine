#pragma once

#include "EventSystem/Event.h"

namespace WaveEngine
{
	struct EntityChangeLayer : public Event
	{
		unsigned int ID = 0;
		int oldLayer = 0;
		int newLayer = 0;

		EntityChangeLayer(const unsigned int& ID, const int& oldLayer, const int& newLayer)
		{
			this->ID = ID;
			this->oldLayer = oldLayer;
			this->newLayer = newLayer;
		}

		EntityChangeLayer()
		{
		}

		void Reset() override
		{
			ID = 0;
			oldLayer = 0;
			newLayer = 0;
		}
	};
}
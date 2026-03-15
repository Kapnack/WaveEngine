#pragma once

#include "EventSystem/Event.h"

namespace WaveEngine
{
	struct DestroyEntity : public Event
	{
		unsigned int ID = 0;

		DestroyEntity(const unsigned int& ID)
		{
			this->ID = ID;
		}

		DestroyEntity()
		{
		}

		void Reset() override
		{
			ID = 0;
		}
	};
}
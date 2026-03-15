#pragma once

#include "Entity/Component/Component.h"

namespace WaveEngine
{
	class CameraComp : public Component
	{
	public:

		void Update() override;
	};
}
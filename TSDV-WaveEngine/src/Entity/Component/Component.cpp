#include "Component.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Time/Time.h"

namespace WaveEngine
{
	Component::Component()
	{
	}

	Component::~Component()
	{
	}

	Entity& Component::GetEntity()
	{
		return *entity;
	}

	float Component::GetDeltaTime()
	{
		return ServiceProvider::Instance().Get<Time>()->GetDeltaTime();
	}

	Input& Component::GetInput()
	{
		return *ServiceProvider::Instance().Get<Input>();
	}
}
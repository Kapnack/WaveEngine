#include "CameraComp.h"

#include <WaveMath/Vector3/Vector3.h>

#include "Entity/Entity.h"
#include "Input/Input.h"

namespace WaveEngine
{
	void CameraComp::Update()
	{
		if (GetInput().IsKeyPressed(Keys::W))
		{
			GetEntity().Translate(Vector3::Up() * GetDeltaTime() * 100);
		}
		else if (GetInput().IsKeyPressed(Keys::A))
		{
			GetEntity().Translate(Vector3::Left() * GetDeltaTime() * 100);
		}
		else if (GetInput().IsKeyPressed(Keys::S))
		{
			GetEntity().Translate(Vector3::Down() * GetDeltaTime() * 100);
		}
		else if (GetInput().IsKeyPressed(Keys::D))
		{
			GetEntity().Translate(Vector3::Right() * GetDeltaTime() * 100);
		}

		if (GetInput().IsKeyPressed(Keys::SPACE))
		{
			GetEntity().Translate(Vector3::Foward() * GetDeltaTime() * 100);
		}
		else if (GetInput().IsKeyPressed(Keys::LEFT_CONTROL))
		{
			GetEntity().Translate(Vector3::Back() * GetDeltaTime() * 100);
		}
	}
}
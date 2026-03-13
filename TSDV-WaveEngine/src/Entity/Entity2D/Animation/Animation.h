#pragma once

#include "Export.h"
#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	class Frame
	{
	public:

		Vector2 topLeft;
		Vector2 bottomRight;

		void* instance = nullptr;
		void* method = nullptr;
		void(*invoke)(void*, void*) = nullptr;

		Frame()
		{
		}

		Frame(const Vector2& topLeft, const Vector2& bottomRight)
		{
			this->topLeft = topLeft;
			this->bottomRight = bottomRight;
		}

		void SetCallback(void(*func)())
		{
			method = *(void**)&func;

			invoke =
				[](void*, void* m)
				{
					void(*callback)() = reinterpret_cast<void(*)()>(m);
					callback();
				};
		}

		template<typename T>
		void SetCallback(T* instance, void(T::* func)())
		{
			this->instance = instance;

			method = *(void**)&func;

			invoke =
				[](void* instance, void* m)
				{
					T* o = static_cast<T*>(instance);
					void(T:: * callback)() = *(void(T::**)()) & m;
					(o->*callback)();
				};
		}

		void Invoke()
		{
			if (invoke)
				invoke(instance, method);
		}
	};

	WAVEEXPORT class Animation
	{
	private:

		const static float DEFAULT_SPEED;

		float currentTime = 0;
		float animationTime = 0;
		float timePerFrame = 0;
		int framesQuantity = 0;
		float animationSpeed = DEFAULT_SPEED;

		Frame* frames = nullptr;

		int previousFrame = -1;
		unsigned int currentFrame = 0;

		bool paused = false;

		void KeepTimerInBounds();
		void SetCurrentFrame();
		void AddToTimer(const float& addition);

	public:

		WAVEEXPORT Animation(const Vector2& startCoords,
			const Vector2& frameArea,
			const Vector2& textureArea,
			const int& framesQuantity,
			const float& animationTime);

		WAVEEXPORT ~Animation();
		WAVEEXPORT void Update(const float& deltaTime);
		WAVEEXPORT void MoveToNextFrame();
		WAVEEXPORT void MoveToPreviousFrame();
		WAVEEXPORT void GoToFrame(const int& index);
		WAVEEXPORT void ResetTime();
		WAVEEXPORT void Pause();
		WAVEEXPORT void UnPause();
		WAVEEXPORT void SetPause(const bool& paused);
		WAVEEXPORT void SwitchPauseState();
		WAVEEXPORT bool GetPause();
		WAVEEXPORT bool DidChangeFrame();

		WAVEEXPORT void SetSpeed(const float& speed);

		WAVEEXPORT Frame GetCurrentFrame() const;
		WAVEEXPORT Frame GetFrame(int index) const;

		WAVEEXPORT void SetCallbackToFrame(const int& index, void(*func)());

		template<typename T>
		void SetCallbackToFrame(const int& index, T* instance, void(T::* func)())
		{
			if (index >= framesQuantity)
				return;

			frames[index].SetCallback(instance, func);
		}
	};
}
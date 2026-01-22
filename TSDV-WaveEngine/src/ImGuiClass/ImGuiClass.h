#pragma once

#include "ServiceProvider/Service.h"

#include <GLFW/glfw3.h>

class BaseGame;
class ServiceProvider;

namespace WaveEngine::ImGuiClass
{
	class ImGuiClass : public Service
	{
	private:

		ImGuiClass(GLFWwindow* window);
		~ImGuiClass();

		void Init(GLFWwindow* window);
		void Update();
		void Unload();

		friend class BaseGame;
		friend class ServiceProvider;

	public:


	};
}


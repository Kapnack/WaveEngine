#include "Window/Window.h"
#include "Renderer/Renderer.h"

int main()
{
	Window window = Window(800, 600, "Wavendow");

	window.Init();

	Renderer renderer;

	float positions[6]
	{
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	renderer.Init(positions);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);

		for (int i = 0; i < 6; i += 2)
			glVertex2f(positions[i], positions[i + 1]);

		glEnd();

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	renderer.Unload();
	window.Unload();

	return 0;
}
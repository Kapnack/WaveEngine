#include "Window/Window.h"
#include "Renderer/Renderer.h"

int main()
{
	Window* window = new Window(800, 600, "Wavendow");

	window->Init();

	Renderer* renderer = new Renderer;

	renderer->Init();

	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(renderer->shader.GetProgram());

		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}

	renderer->Unload();
	window->Unload();

	delete renderer;
	delete window;

	return 0;
}
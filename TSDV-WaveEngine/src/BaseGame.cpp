#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity2D/Shape/Shape.h"

int main()
{
	Window* window = new Window(800, 600, "Wavendow");

	window->Init();

	Renderer* renderer = new Renderer;

	renderer->Init();

	Shape shape;

	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(renderer->shader.GetProgram());

		shape.Draw();

		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}

	renderer->Unload();
	window->Unload();

	delete renderer;
	delete window;

	return 0;
}
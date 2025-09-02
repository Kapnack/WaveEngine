#include "Window/Window.h"
#include "Renderer/Renderer.h"

int main()
{
	Window window = Window(800, 600, "Wavendow");

	window.Init();

	Renderer renderer;

	float positions[] =
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] =
	{  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	renderer.Init(positions, indices);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	renderer.Unload();
	window.Unload();

	return 0;
}
#include "Engine/Game/Game.h"
#include "Entity/Entity2D/Shape/Square/Square.h"

int main()
{
	/*
	Window* window = new Window(800, 600, "Wavendow");

	Renderer* renderer = new Renderer;

	Vector3 pos;

	Square shape = Square(renderer, pos);

	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(renderer->shader.GetProgram());

		shape.Draw();

		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}

	delete renderer;
	delete window;

	return 0;
	*/

	Game* game = new Game(800, 600);

	game->Loop();

	game->Unload();

	delete game;
}
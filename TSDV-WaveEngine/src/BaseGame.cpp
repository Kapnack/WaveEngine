#include "Window/Window.h"
#include "Renderer/Renderer.h"

using namespace std;

int main()
{
	Window window = Window(800, 600, "Wavendow");

	window.Init();

	Renderer renderer = Renderer(window);

	renderer.Init();

	renderer.Update();

	window.Unload();

	return 0;
}
#include "Square.h"

Square::Square(Renderer* renderer, Vector3 position) : Shape(renderer, position)
{
	vertexSize = 12.0f;
	vertex = new float[vertexSize]
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	indexSize = 6;
	indices = new int[indexSize]
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::~Square()
{
}

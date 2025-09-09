#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, Vector3 position) : Shape(renderer, position)
{
	vertexSize = 9.0f;

	vertex = new float[vertexSize]
		{
			1.0f, 1.0f, 0.5f,  // top right
				1.0f, 0.0f, 0.5f,  // bottom right
				0.0f, 1.0f, 0.5f,  // bottom left
		};

	indexSize = 3;
	indices = new int[indexSize]
		{
			0, 1, 2
		};

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Triangle::~Triangle()
{
}

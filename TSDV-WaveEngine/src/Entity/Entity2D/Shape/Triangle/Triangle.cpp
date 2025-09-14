#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, Vector3 position) : Shape(renderer, position)
{
	vertexSize = 3;

	vertex = new VertexPosColor[vertexSize]
	{
		VertexPosColor(0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f),  // bottom right
		VertexPosColor(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f),  // bottom left
		VertexPosColor(0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f)    // top
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

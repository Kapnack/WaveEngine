#include "Square.h"

Square::Square(Renderer* renderer, Vector3 position) : Shape(renderer, position)
{
	vertexSize = 4;

	vertex = new VertexPosColor[vertexSize]
	{
	VertexPosColor(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f),
	VertexPosColor(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f),
	VertexPosColor(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f),
	VertexPosColor(-0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f)
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

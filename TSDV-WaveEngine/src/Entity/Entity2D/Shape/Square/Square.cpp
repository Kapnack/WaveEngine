#include "Square.h"

#include "Vector4.h"

Square::Square(Renderer* renderer, Vector4 color) : Shape(renderer)
{
	vertexSize = 4;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, 0.5f, 0.0f), color),
		VertexData(Vector3(0.5f, -0.5f, 0.0f), color),
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), color),
		VertexData(Vector3(-0.5f, 0.5f, 0.0f), color)
	};

	indexSize = 6;
	indices = new int[indexSize]
		{
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::Square(Renderer* renderer) : Shape(renderer)
{
	vertexSize = 4;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, 0.5f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f)),
		VertexData(Vector3(0.5f, -0.5f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f)),
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f)),
		VertexData(Vector3(-0.5f, 0.5f, 0.0f), Vector4(0.5f, 0.0f, 0.5f, 1.0f))
	};

	indexSize = 6;
	indices = new int[indexSize]
		{
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

	SetTRS();

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::~Square()
{
}

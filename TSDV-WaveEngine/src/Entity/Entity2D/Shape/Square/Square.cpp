#include "Square.h"

#include "Vector4.h"

Square::Square() : Shape()
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

	GetRenderer()->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::Square(Vector4 color) : Shape()
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

	GetRenderer()->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::~Square()
{
}

#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, Vector4 color) : Shape(renderer)
{
	vertexSize = 3;

	vertex = new VertexData[vertexSize]
	{
		VertexData(0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),  // bottom right
		VertexData(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),  // bottom left
		VertexData(0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f)    // top
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

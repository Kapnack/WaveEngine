#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, Vector3 position, Vector4 color) : Shape(renderer, position)
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

	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Scale

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Triangle::~Triangle()
{
}

#include "Square.h"

#include "Vector4.h"

Square::Square(Renderer* renderer, Vector3 position, Vector4 color) : Shape(renderer, position)
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

	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(5.0f, 3.5f, 2.2f)); // Translate
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Scale

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::Square(Renderer* renderer, Vector3 position) : Shape(renderer, position)
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

	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(1.0f, 0.5f, 0.2f)); // Translate
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Scale

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::~Square()
{
}

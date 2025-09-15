#include "Square.h"

Square::Square(Renderer* renderer, Vector3 position, Vector4 color) : Shape(renderer, position)
{
	vertexSize = 4;

	vertex = new VertexPosColor[vertexSize]
	{
		VertexPosColor(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		VertexPosColor(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		VertexPosColor(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		VertexPosColor(-0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f)
	};

	indexSize = 6;
	indices = new int[indexSize]
		{
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

	model = glm::mat4(1.0f);                    // Identity
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Scale

	renderer->CreateBuffers(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);
}

Square::~Square()
{
}

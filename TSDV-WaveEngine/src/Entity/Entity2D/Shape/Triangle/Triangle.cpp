#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, Vector4 color) : Shape(renderer)
{
	vertexSize = 3;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, -0.5f, 0.0f), color),  // bottom right
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), color),  // bottom left
		VertexData(Vector3(0.0f,  0.5f, 0.0f), color)    // top
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

Triangle::Triangle(Renderer* renderer) : Shape(renderer)
{
	vertexSize = 3;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, -0.5f, 0.0f), Vector4(1,0,0,1)),  // bottom right
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), Vector4(0,1,0,1)),  // bottom left
		VertexData(Vector3(0.0f,  0.5f, 0.0f), Vector4(0,0,1,1))    // top
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

#include "Sprite.h"

Sprite::Sprite(unsigned int texture, Renderer* renderer) : Entity2D(renderer)
{
	vertexSize = 4;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, 0.5f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), TextureData(1,1)),
		VertexData(Vector3(0.5f, -0.5f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), TextureData(1,0)),
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), TextureData(0,0)),
		VertexData(Vector3(-0.5f, 0.5f, 0.0f), Vector4(0.5f, 0.0f, 0.5f, 1.0f), TextureData(0,1))
	};

	indexSize = 6;
	indices = new int[indexSize]
		{
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

	SetTRS();

	this->texture = texture;

	renderer->CreateBuffersSprite(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO, texture);
}

Sprite::Sprite(unsigned int texture, Vector4 color, Renderer* renderer) : Entity2D(renderer)
{
	vertexSize = 4;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, 0.5f, 0.0f), color, TextureData(1,1)),
		VertexData(Vector3(0.5f, -0.5f, 0.0f), color, TextureData(1,0)),
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), color, TextureData(0,0)),
		VertexData(Vector3(-0.5f, 0.5f, 0.0f), color, TextureData(0,1))
	};

	indexSize = 6;
	indices = new int[indexSize]
		{
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

	SetTRS();

	this->texture = texture;

	renderer->CreateBuffersSprite(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO, texture);
}

Sprite::~Sprite()
{
}

void Sprite::Draw()
{
	renderer->DrawElementSprite(model, indexSize, VAO, texture);
}

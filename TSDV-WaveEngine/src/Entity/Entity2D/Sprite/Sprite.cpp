#include "Sprite.h"

#include "Material/MaterialManager.h"
#include "ServiceProvider/ServiceProvider.h"

Sprite::Sprite(unsigned int texture) : Entity2D()
{
	Init(texture, Vector4{ 1,1,1,1 });

	SetColor(Vector4(1, 1, 1, 1));
}

Sprite::Sprite(unsigned int texture, Vector4 color) : Entity2D()
{
	Init(texture, color);
}

void Sprite::Init(unsigned int texture, Vector4 color)
{
	vertexSize = 4;

	vertex = new VertexData[vertexSize]
	{
		VertexData(Vector3(0.5f, 0.5f, 0.0f), color, Vector2(1,1)),
		VertexData(Vector3(0.5f, -0.5f, 0.0f), color, Vector2(1,0)),
		VertexData(Vector3(-0.5f, -0.5f, 0.0f), color, Vector2(0,0)),
		VertexData(Vector3(-0.5f, 0.5f, 0.0f), color, Vector2(0,1))
	};

	indexSize = 6;
	indices = new int[indexSize]
		{
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

	SetTRS();

	this->texture = texture;

	GetRenderer()->CreateBuffersSprite(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO, texture);

	material = &ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial("basicSpriteMaterial");
}

Sprite::~Sprite()
{
}

void Sprite::SetUVCordinates(Vector2 leftTopUvCoords, Vector2 rightBottomUvCoords)
{
	const unsigned int FIRST_VERTEX_U = 7;

	const unsigned int SECOND_VERTEX_U = 16;

	const unsigned int THIRD_VERTEX_U = 25;

	const unsigned int FOURTH_VERTEX_U = 34;


	vertex[0].textureCordinates.x = rightBottomUvCoords.x;
	vertex[0].textureCordinates.y = leftTopUvCoords.y;

	vertex[1].textureCordinates.x = rightBottomUvCoords.x;
	vertex[1].textureCordinates.y = rightBottomUvCoords.y;

	vertex[2].textureCordinates.x = leftTopUvCoords.x;
	vertex[2].textureCordinates.y = rightBottomUvCoords.y;

	vertex[3].textureCordinates.x = leftTopUvCoords.x;
	vertex[3].textureCordinates.y = leftTopUvCoords.y;

	GetRenderer()->UpdateBuffer(vertex, vertexSize, VBO);
}

void Sprite::SetAnimation(Animation* animation)
{
	if (this->animation == animation)
		return;

	if (this->animation)
		this->animation->ResetTime();

	this->animation = animation;
}

void Sprite::Update()
{
	if (animation)
		animation->Update();
}

void Sprite::Draw()
{
	if (animation)
	{
		Frame frame = this->animation->GetCurrentFrame();
		SetUVCordinates(frame.topLeft, frame.bottomRight);
	}

	GetRenderer()->DrawElementSprite(model, material, indexSize, VAO, texture);
}

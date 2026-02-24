#include "Sprite.h"

#include "Material/MaterialManager.h"
#include "ServiceProvider/ServiceProvider.h"

Sprite::Sprite(const unsigned int& ID) : Entity2D(ID), Drawable(ID)
{
	Init(Vector4{ 1,1,1,1 });

	SetColor(Vector4(1, 1, 1, 1));
}

void Sprite::Init(const Vector4& color)
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

	CalculateTRS();

	this->textureID = textureID;

	GetRenderer()->CreateBuffersSprite(vertex, vertexSize, indices, indexSize, VAO, VBO, EBO);

	materialID = ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial("basicSpriteMaterial");
}

Sprite::~Sprite()
{
}

void Sprite::SetUVCordinates(const Vector2& leftTopUvCoords, const Vector2& rightBottomUvCoords)
{
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

void Sprite::SetTexture(const unsigned int& textureID)
{
	this->textureID = textureID;
}

unsigned int Sprite::GetTexture()
{
	return textureID;
}

void Sprite::Draw()
{
	if (!GetIsActive())
		return;

	if (animation)
	{
		Frame frame = animation->GetCurrentFrame();
		SetUVCordinates(frame.topLeft, frame.bottomRight);
	}

	GetRenderer()->DrawElementSprite(model, materialID, indexSize, VAO, textureID);
}

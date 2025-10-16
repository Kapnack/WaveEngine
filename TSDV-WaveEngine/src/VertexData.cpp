#include "VertexData.h"

VertexData::VertexData()
{
}

VertexData::VertexData(float x, float y, float z, float r, float g, float b, float a)
{
	position.x = x;
	position.y = y;
	position.z = z;

	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

VertexData::VertexData(Vector3 position, Vector4 color)
{
	this->position = position;
	this->color = color;
}

VertexData::VertexData(Vector3 position, Vector4 color, TextureData textureCordinates)
{
	this->position = position;
	this->color = color;
	this->textureCordinates = textureCordinates;
}

void VertexData::SetColor(Vector4 color)
{
	this->color = color;
}

TextureData::TextureData()
{
}

TextureData::TextureData(float u, float v)
{
	this->u = u;
	this->v = v;
}

#include "VertexPosColor.h"

VertexPosColor::VertexPosColor()
{
}

VertexPosColor::VertexPosColor(float x, float y, float z, float r, float g, float b, float a)
{
	position.x = x;
	position.y = y;
	position.z = z;

	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

VertexPosColor::VertexPosColor(Vector3 position, Vector4 color)
{
	this->position = position;
	this->color = color;
}

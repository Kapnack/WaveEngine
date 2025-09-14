#include "VertexPosColor.h"

VertexPosColor::VertexPosColor()
{
}

VertexPosColor::VertexPosColor(float x, float y, float z, float r, float g, float b)
{
	position.x = x;
	position.y = y;
	position.z = z;

	color.x = r;
	color.y = g;
	color.z = b;
}

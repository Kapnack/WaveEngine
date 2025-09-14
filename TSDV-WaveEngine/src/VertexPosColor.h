#pragma once

#include <vector>
#include "Vector3.h"

using namespace std;

struct VertexPosColor
{
	Vector3 position;

	Vector3 color;

	VertexPosColor();
	VertexPosColor(float v1, float v2, float v3, float r, float g, float b);
};
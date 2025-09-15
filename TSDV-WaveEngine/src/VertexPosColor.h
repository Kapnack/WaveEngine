#pragma once

#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include "Export.h"

using namespace std;

WAVEEXPORT struct VertexPosColor
{
	Vector3 position;

	Vector4 color;

	WAVEEXPORT VertexPosColor();
	WAVEEXPORT VertexPosColor(float v1, float v2, float v3, float r, float g, float b, float a);
	WAVEEXPORT VertexPosColor(Vector3 position, Vector4 color);
};
#pragma once

#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include "Export.h"

using namespace std;

WAVEEXPORT struct VertexData
{
	Vector3 position;

	Vector4 color;

	WAVEEXPORT VertexData();
	WAVEEXPORT VertexData(float v1, float v2, float v3, float r, float g, float b, float a);
	WAVEEXPORT VertexData(Vector3 position, Vector4 color);
};
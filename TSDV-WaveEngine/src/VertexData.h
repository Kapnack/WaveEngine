#pragma once

#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include "Export.h"
#include <Entity/Entity2D/Animation/Animation.h>

using namespace std;

struct TextureData
{
	float u = 0;
	float v = 0;

	WAVEEXPORT TextureData();
	WAVEEXPORT TextureData(float u, float v);
};

WAVEEXPORT struct VertexData
{
	Vector3 position;

	Vector4 color;

	Vector2 textureCordinates;

	float textureID = 0;

	WAVEEXPORT VertexData();
	WAVEEXPORT VertexData(float v1, float v2, float v3, float r, float g, float b, float a);
	WAVEEXPORT VertexData(Vector3 position, Vector4 color);
	WAVEEXPORT VertexData(Vector3 position, Vector4 color, Vector2 textureCordinates);

	WAVEEXPORT void SetColor(Vector4 color);
};
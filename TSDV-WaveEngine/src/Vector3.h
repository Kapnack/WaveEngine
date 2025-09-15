#pragma once

#include "Export.h"

WAVEEXPORT struct Vector3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	WAVEEXPORT Vector3();
	WAVEEXPORT Vector3(float x, float y, float z);
};
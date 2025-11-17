#pragma once

#include "Export.h"

WAVEEXPORT struct Vector3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	WAVEEXPORT Vector3();
	WAVEEXPORT Vector3(float x, float y, float z);
	WAVEEXPORT Vector3 operator/(Vector3 other);
	WAVEEXPORT void operator+=(Vector3 other);
	WAVEEXPORT void operator-=(Vector3 other);
	WAVEEXPORT Vector3 operator*(float scalar);
	WAVEEXPORT friend Vector3 operator*(float scalar, Vector3 vector3);

	WAVEEXPORT static Vector3 Up();
	WAVEEXPORT static Vector3 Down();
	WAVEEXPORT static Vector3 Left();
	WAVEEXPORT static Vector3 Right();
	WAVEEXPORT static Vector3 One();
};
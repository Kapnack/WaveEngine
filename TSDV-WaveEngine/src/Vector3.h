#pragma once

#include "Export.h"

struct Vector2;

WAVEEXPORT struct Vector3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	WAVEEXPORT Vector3();

	WAVEEXPORT Vector3(const Vector2& vector2);
	WAVEEXPORT Vector3(const float& x, const float& y);
	WAVEEXPORT Vector3(const float& x, const float& y, const float& z);
	WAVEEXPORT Vector3 operator/(const Vector3& other);
	WAVEEXPORT void operator+=(const Vector3& other);
	WAVEEXPORT void operator-=(const Vector3& other);
	WAVEEXPORT void operator=(const Vector2& vector2);
	WAVEEXPORT Vector3 operator*(const float& scalar);
	WAVEEXPORT friend Vector3 operator*(const float& scalar, const Vector3& vector3);

	WAVEEXPORT static Vector3 Up();
	WAVEEXPORT static Vector3 Down();
	WAVEEXPORT static Vector3 Right();
	WAVEEXPORT static Vector3 Left();
	WAVEEXPORT static Vector3 One();
	WAVEEXPORT static Vector3 Front();
	WAVEEXPORT static Vector3 Back();
};
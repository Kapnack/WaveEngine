#pragma once

#include "Export.h"

#include "../Quaternion/Quaternion.h"

WAVEEXPORT struct Matrix4x4 final
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;

	Matrix4x4();
	Matrix4x4(const float& m00, const float& m01, const float& m02, const float& m03,
			const float& m10, const float& m11, const float& m12, const float& m13, 
			const float& m20, const float& m21, const float& m22, const float& m23,
			const float& m30, const float& m31, const float& m32, const float& m33);
	Matrix4x4(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3);
	~Matrix4x4();

	WAVEEXPORT void SetTranslate(const Vector3& vector);
	WAVEEXPORT void AddTranslate(const Vector3& vector);
	WAVEEXPORT Matrix4x4 GetTranslate() const;
	WAVEEXPORT void SetScale(const Vector3& vector);
	WAVEEXPORT void AddScale(const Vector3& vector);
	WAVEEXPORT Matrix4x4 GetScale() const;

	WAVEEXPORT Vector3 GetColumn(const int& index);
	WAVEEXPORT Vector3 SetColumn(const int& index, const Vector3& vector);
	WAVEEXPORT Vector3 GetRow(const int& index);
	WAVEEXPORT Vector3 SetRow(const int& index, const Vector3& vector);

	Matrix4x4 operator*(const Matrix4x4& other) const;

	WAVEEXPORT static Matrix4x4 Identity();
	WAVEEXPORT static Matrix4x4 Scale(const float& x, const float& y, const float& z);
	WAVEEXPORT static Matrix4x4 Scale(const Vector3& vector);
	WAVEEXPORT static Matrix4x4 Rotate(const float& x, const float& y, const float& z, const float& w);
	WAVEEXPORT static Matrix4x4 Rotate(const Quaternion& quaternian);
	WAVEEXPORT static Matrix4x4 Translate(const float& x, const float& y, const float& z);
	WAVEEXPORT static Matrix4x4 Translate(const Vector3& vector);

	WAVEEXPORT static Matrix4x4 TRS(const Vector3& t, const Quaternion& r, const Vector3& s);
	WAVEEXPORT static Matrix4x4 TRS(const Matrix4x4& t, const Matrix4x4& r, const Matrix4x4& s);
};


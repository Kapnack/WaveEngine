#include "Matrix4x4.h"

#include <stdexcept> 

Matrix4x4::Matrix4x4()
{
	*this = Identity();
}

Matrix4x4::Matrix4x4(const float& m00, const float& m01, const float& m02, const float& m03, const float& m10, const float& m11, const float& m12, const float& m13, const float& m20, const float& m21, const float& m22, const float& m23, const float& m30, const float& m31, const float& m32, const float& m33)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}

Matrix4x4::Matrix4x4(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3)
{
	m00 = q0.x; m01 = q0.y; m02 = q0.z; m03 = q0.w;
	m10 = q1.x; m11 = q1.y; m12 = q1.z; m13 = q0.w;
	m20 = q2.x; m21 = q2.y; m22 = q2.z; m23 = q2.w;
	m30 = q3.x; m31 = q3.y; m32 = q3.z; m33 = q3.w;
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::SetTranslate(const Vector3& vector)
{
	m03 = vector.x;
	m13 = vector.y;
	m23 = vector.z;
}

void Matrix4x4::AddTranslate(const Vector3& vector)
{
	m03 += vector.x;
	m13 += vector.y;
	m23 += vector.z;
}

Matrix4x4 Matrix4x4::GetTranslate() const
{
	return Translate(m03, m13, m23);
}

void Matrix4x4::SetScale(const Vector3& vector)
{
	m00 = vector.x;
	m11 = vector.y;
	m22 = vector.z;
}

void Matrix4x4::AddScale(const Vector3& vector)
{
	m00 *= vector.x;
	m11 *= vector.y;
	m22 *= vector.z;
}

Matrix4x4 Matrix4x4::GetScale() const
{
	return Scale(m00, m11, m22);
}

Vector3 Matrix4x4::GetColumn(const int& index)
{
	switch (index)
	{
	case 0: return Vector3(m00, m01, m02);
	case 1: return Vector3(m10, m11, m12);
	case 2: return Vector3(m20, m21, m22);
	case 3: return Vector3(m30, m31, m32);
	default: throw std::out_of_range("Indices must be between 0 and 3.");
	}

	return Vector3::Zero();
}

Vector3 Matrix4x4::SetColumn(const int& index, const Vector3& vector)
{
	switch (index)
	{
	case 0:
		m00 = vector.x;
		m10 = vector.y;
		m20 = vector.z;
		m30 = 0.0f;
		break;

	case 1:
		m01 = vector.x;
		m11 = vector.y;
		m21 = vector.z;
		m31 = 0.0f;
		break;

	case 2:
		m02 = vector.x;
		m12 = vector.y;
		m22 = vector.z;
		m32 = 0.0f;
		break;

	case 3:
		m03 = vector.x;
		m13 = vector.y;
		m23 = vector.z;
		m33 = 0.0f;
		break;

	default: throw std::out_of_range("Indices must be between 0 and 3.");
	}
}

Vector3 Matrix4x4::GetRow(const int& index)
{
	switch (index)
	{
	case 0: return Vector3(m00, m01, m03);
	case 1: return Vector3(m01, m12, m13);
	case 2: return Vector3(m02, m21, m23);
	case 3: return Vector3(m03, m31, m33);
	default:throw std::out_of_range("Row index must be 0 to 3");
	}
}

Vector3 Matrix4x4::SetRow(const int& index, const Vector3& vector)
{
	switch (index)
	{
	case 0:
		m00 = vector.x;
		m01 = vector.y;
		m02 = vector.z;
		m03 = 0.0f;
		break;
	case 1:
		m10 = vector.x;
		m11 = vector.y;
		m12 = vector.z;
		m13 = 0.0f;
		break;
	case 2:
		m20 = vector.x;
		m21 = vector.y;
		m22 = vector.z;
		m23 = 0.0f;
		break;
	case 3:
		m30 = vector.x;
		m31 = vector.y;
		m32 = vector.z;
		m33 = 0.0f;
		break;
	default:throw std::out_of_range("Row index must be 0 to 3");
	}
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
	return Matrix4x4
	(
		m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
		m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
		m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
		m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,

		m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
		m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
		m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
		m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,

		m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
		m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
		m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
		m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,

		m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
		m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
		m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
		m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33
	);
}

Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::Scale(const float& x, const float& y, const float& z)
{
	Matrix4x4 scale;

	scale.m00 = x;
	scale.m11 = y;
	scale.m22 = z;

	return scale;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vector)
{
	return Scale(vector.x, vector.y, vector.z);
}

Matrix4x4 Matrix4x4::Rotate(const float& x, const float& y, const float& z, const float& w)
{
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	Matrix4x4 m;
	m.m00 = 1.0f - 2.0f * (yy + zz);
	m.m01 = 2.0f * (xy - wz);
	m.m02 = 2.0f * (xz + wy);

	m.m10 = 2.0f * (xy + wz);
	m.m11 = 1.0f - 2.0f * (xx + zz);
	m.m12 = 2.0f * (yz - wx);

	m.m20 = 2.0f * (xz - wy);
	m.m21 = 2.0f * (yz + wx);
	m.m22 = 1.0f - 2.0f * (xx + yy);

	return m;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& q)
{
	return Rotate(q.x, q.y, q.z, q.w);
}

Matrix4x4 Matrix4x4::Translate(const float& x, const float& y, const float& z)
{
	Matrix4x4 translate;

	translate.m03 = x;
	translate.m13 = y;
	translate.m23 = z;

	return translate;
}

Matrix4x4 Matrix4x4::Translate(const Vector3& vector)
{
	return Translate(vector.x, vector.y, vector.z);
}

Matrix4x4 Matrix4x4::TRS(const Vector3& t, const Quaternion& r, const Vector3& s)
{
	const Matrix4x4 translate = Translate(t);
	const Matrix4x4 rotate = Rotate(r);
	const Matrix4x4 scale = Scale(s);

	return TRS(translate, rotate, scale);
}

Matrix4x4 Matrix4x4::TRS(const Matrix4x4& t, const Matrix4x4& r, const Matrix4x4& s)
{
	return t * r * s;
}

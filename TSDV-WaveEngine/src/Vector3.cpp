#include "Vector3.h"

#include "Vector2.h"

Vector3::Vector3()
{
}

Vector3::Vector3(const Vector2& vector2)
{
	Vector3(vector2.x, vector2.y);
}

Vector3::Vector3(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Vector3::Vector3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator/(const Vector3& other)
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

void Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vector3::operator=(const Vector2& vector2)
{
	x = vector2.x;
	y = vector2.y;
}

Vector3 Vector3::operator*(const float& scalar)
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 operator*(const float& scalar, const Vector3& vector3)
{
	return Vector3(vector3.x * scalar, vector3.y * scalar, vector3.z * scalar);
}

Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}

Vector3 Vector3::Up()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::Down()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::Right()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Left()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Front()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::Back()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}


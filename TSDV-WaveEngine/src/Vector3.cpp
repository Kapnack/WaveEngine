#include "Vector3.h"


Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator/(Vector3 other)
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

void Vector3::operator+=(Vector3 other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator-=(Vector3 other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

Vector3 Vector3::operator*(float scalar)
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 operator*(float scalar, Vector3 vector3)
{
	return Vector3(vector3.x * scalar, vector3.y * scalar, vector3.z * scalar);
}

Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Down()
{
	return -1.0f * Up();
}

Vector3 Vector3::Left()
{
	return Vector3(-1, 0, 0);
}

Vector3 Vector3::Right()
{
	return -1.0f * Left();
}

Vector3 Vector3::Z()
{
	return Vector3(0, 0, 1);
}


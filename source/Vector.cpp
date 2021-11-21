#include "Vector.h"
#include <math.h>

Vec2::Vec2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vec2::Vec2(float num)
{
	this->x = num;
	this->y = num;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vec2::Set(float x)
{
	this->x = x;
	this->y = x;
}

void Vec2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2& v)
{
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v)
{
	return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(const float& f)
{
	return Vec2(x * f, y * f);
}

Vec2 Vec2::operator/(const float& f)
{
	return Vec2(x / f, y / f);
}

float Vec2::Lenght()
{
	return sqrt((x * x) + (y * y));
}

void Vec2::Normalize()
{
	float len = Lenght();
	this->x /= len;
	this->y /= len;
}

Vec3::Vec3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vec3::Vec3(float num)
{
	this->x = num;
	this->y = num;
	this->z = num;
}

Vec3::Vec3(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.0f;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vec3::Set(float x)
{
	this->x = x;
	this->y = x;
	this->z = x;
}

void Vec3::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator+(const Vec3& v)
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v)
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(const float& f)
{
	return Vec3(x * f, y * f, z* f);
}

Vec3 Vec3::operator/(const float& f)
{
	//TODO: Division by Zero control
	return Vec3(x / f, y / f, z / f);
}

float Vec3::Lenght()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

void Vec3::Normalize()
{
	float len = Lenght();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}

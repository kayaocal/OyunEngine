#include "Vector.h"
#include <math.h>

Vec2::Vec2()
{
	X = 0.0f;
	Y = 0.0f;
}

Vec2::Vec2(float num)
{
	X = num;
	Y = num;
}

Vec2::Vec2(float x, float y)
{
	X = x;
	Y = y;
}

void Vec2::Set(float x)
{
	X = x;
	Y = x;
}

void Vec2::Set(float x, float y)
{
	X = x;
	Y = y;
}

Vec2 Vec2::operator+(const Vec2& v)
{
	return Vec2(X + v.X, Y + v.Y);
}

Vec2 Vec2::operator-(const Vec2& v)
{
	return Vec2(X - v.X, Y - v.Y);
}

Vec2 Vec2::operator*(const float& f)
{
	return Vec2(X * f, Y * f);
}

Vec2 Vec2::operator/(const float& f)
{
	return Vec2(X / f, Y / f);
}

float Vec2::Lenght()
{
	return sqrt((X * X) + (Y * Y));
}

void Vec2::Normalize()
{
	float len = Lenght();
	X /= len;
	Y /= len;
}

Vec3::Vec3()
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}

Vec3::Vec3(float num)
{
	X = num;
	Y = num;
	Z = num;
}

Vec3::Vec3(float x, float y)
{
	X = x;
	Y = y;
	Z = 0.0f;
}

Vec3::Vec3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

void Vec3::Set(float x)
{
	X = x;
	Y = x;
	Z = x;
}

void Vec3::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vec3 Vec3::operator+(const Vec3& v)
{
	return Vec3(X + v.X, Y + v.Y, Z + v.Z);
}

Vec3 Vec3::operator-(const Vec3& v)
{
	return Vec3(X - v.X, Y - v.Y, Z - v.Z);
}

Vec3 Vec3::operator*(const float& f)
{
	return Vec3(X * f, Y * f, Z* f);
}

Vec3 Vec3::operator/(const float& f)
{
	//TODO: Division by Zero control
	return Vec3(X / f, Y / f, Z / f);
}

float Vec3::Lenght()
{
	return sqrt((X * X) + (Y * Y) + (Z * Z));
}

void Vec3::Normalize()
{
	float len = Lenght();
	X /= len;
	Y /= len;
	Z /= len;
}

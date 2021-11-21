#pragma once

#include <glm/glm.hpp>

#define EngineExport   __declspec( dllexport )



class EngineExport Vec2
{
	glm::vec2 _Source;

public:

	float x;
	float y;

	Vec2(); //! Generates zero vector
	Vec2(glm::vec2);
	Vec2(float num);
	Vec2(float x, float y);

	void Set(float x);
	void Set(float x, float y);

	Vec2 operator+(const Vec2&);
	Vec2 operator-(const Vec2&);
	Vec2 operator*(const float&);
	Vec2 operator/(const float&);

	float & operator[](int);
	float Lenght();
	void Normalize();

};


class EngineExport Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3(); //! Generates zero vector
	Vec3(float num);
	Vec3(float x, float y);
	Vec3(float x, float y, float z);

	void Set(float x);
	void Set(float x, float y, float z);
	Vec3 operator+(const Vec3&);
	Vec3 operator-(const Vec3&);
	Vec3 operator*(const float&);
	Vec3 operator/(const float&);

	float Lenght();
	void Normalize();

};


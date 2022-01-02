#ifndef OYUN_VECTOR_H__
#define OYUN_VECTOR_H__

#include <glm/glm.hpp>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif


namespace Oyun
{

	class OYUN_API Vec2
	{

	public:

		float x;
		float y;

		Vec2(); //! Generates zero vector
		Vec2(float num);
		Vec2(float x, float y);

		void Set(float x);
		void Set(float x, float y);

		Vec2 operator+(const Vec2&);
		Vec2 operator-(const Vec2&);
		Vec2 operator*(const float&);
		Vec2 operator/(const float&);

		float Lenght();
		void Normalize();

	};


	class OYUN_API Vec3
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

}
#endif //OYUN_VECTOR_H__
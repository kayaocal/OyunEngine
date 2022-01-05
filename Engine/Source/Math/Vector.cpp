#include "Math/Vector.h"

#include "imgui_impl_opengl3_loader.h"

namespace Oyun
{
	Vec2::Vec2()
		:x(0.0f), y(0.0f)
	{
	}

	Vec2::Vec2(float num)
		: x(num), y(num)
	{
	}

	Vec2::Vec2(float v1, float v2)
		:x(v1), y(v2)
	{
	}

	Vec2::Vec2(const Vec2& v)
		: x(v.x), y(v.y)
	{
	}

	Vec2::Vec2(Vec2&& v) noexcept
		:x(std::move(v.x)), y(std::move(v.y))
	{
	}

	void Vec2::Set(float x)
	{
		this->x = x;
	}

	void Vec2::Set(float x, float y)
	{
		this->x = x; 
		this->y = y; 
	}

	void Vec2::operator=(const Vec2& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	void Vec2::operator=(Vec2&& v) noexcept
	{
		this->x = std::move(v.x);
		this->y = std::move(v.y);
	}

	void Vec2::operator+=(const Vec2& v)
	{
		this->x += v.x;
		this->y += v.y;
	}

	void Vec2::operator-=(const Vec2& v)
	{
		this->x -= v.x;
		this->y -= v.y;
	}

	void Vec2::operator*=(const float num)
	{
		this->x *= num;
		this->y *= num;
	}

	void Vec2::operator/=(const float num)
	{
		float mul = 1.0f / num;
		this->x *= mul;
		this->y *= mul;
	}

	float Vec2::Magnitude()
	{
		return sqrt((x * x) + (y * y));	
	}


	float Vec2::MagnitudeSquared()
	{
		return (x * x) + (y * y);	
	}

	void Vec2::Normalize()
	{
		float len = Magnitude();
		operator/=(len);
	}

	class Vec2 Vec2::GetNormalized()
	{
		Vec2 newVec(this->x, this->y);
		newVec.Normalize();
		return newVec;
	}


	float Vec2::Dot(const Vec2& f, const Vec2& s)
	{
		return f.x * s.x + f.y * f.y;
	}

	float Vec2::Dot(const Vec2& s)
	{
		return x * s.x + y * s.y;
	}




	class Vec2 Vec2::operator+(const Vec2& v)
	{
		return Vec2(this->x + v.x, this->y + v.y);
	}

	class Vec2 Vec2::operator-(const Vec2& v)
	{
		return Vec2(this->x - v.x, this->y - v.y);
	}

	class Vec2 Vec2::operator*(const float num)
	{
		return Vec2(this->x * num, this->y * num);
	}

	class Vec2 Vec2::operator/(const float num)
	{
		float mul = 1.0f / num;
		return Vec2(this->x * mul, this->y * mul);
	}

	Vec3::Vec3()
		:x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vec3::Vec3(float num)
		: x(num), y(num), z(num)
	{
	}

	Vec3::Vec3(float v1, float v2, float v3)
		:x(v1), y(v2), z(v3)
	{
	}

	Vec3::Vec3(const Vec3& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	Vec3::Vec3(Vec3&& v) noexcept
		:x(std::move(v.x)), y(std::move(v.y)), z(std::move(v.z))
	{
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

	void Vec3::operator=(const Vec3& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	void Vec3::operator=(Vec3&& v) noexcept
	{
		this->x = std::move(v.x);
		this->y = std::move(v.y);
		this->z = std::move(v.z);
	}

	void Vec3::operator+=(const Vec3& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}

	void Vec3::operator-=(const Vec3& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}

	void Vec3::operator*=(const float num)
	{
		this->x *= num;
		this->y *= num;
		this->z *= num;
	}

	void Vec3::operator/=(const float num)
	{
		float mul = 1.0f / num;
		this->x *= mul;
		this->y *= mul;
		this->z *= mul;
	}

	Vec3 Vec3::operator+(const Vec3& v)
	{
		return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vec3 Vec3::operator-(const Vec3& v)
	{
		return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	Vec3 Vec3::operator*(const float num)
	{
		return Vec3(this->x * num, this->y * num, this->z * num);
	}

	Vec3 Vec3::operator/(const float num)
	{
		float mul = 1.0f / num;
		return Vec3(this->x * mul, this->y * mul, this->z * mul);
	}

	float Vec3::Magnitude()
	{
		return sqrt((x * x) + (y * y) + (z * z));	
	}

	float Vec3::MagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z);	
	}

	void Vec3::Normalize()
	{
		float len = Magnitude();
		operator/=(len);
	}

	Vec3 Vec3::GetNormalized()
	{
		Vec3 newVec(this->x, this->y, this->z);
		newVec.Normalize();
		return newVec;
	}

	float Vec3::Dot(const Vec3& f, const Vec3& s)
	{
		return f.x * s.x + f.y * s.y + f.z * s.z;
	}

	float Vec3::Dot(const Vec3& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vec3 Vec3::Cross(const Vec3& f, const Vec3& s)
	{
		return Vec3(f.y * s.z - f.z * s.y, f.z * s.x - f.x * s.z, f.x * s.y - f.y * s.x);
	}

	Vec3 Vec3::Cross(const Vec3& s)
	{
		return Vec3(y * s.z - z * s.y, z * s.x - x * s.z, x * s.y - y * s.x);
	}

	const Color Red(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Green(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Blue(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Orange(1.0f, 0.64f, 0.0f, 1.0f);
	const Color Cyan(0.0f, 1.0f, 1.0f, 1.0f);
	const Color Magenta(1.0f, 0.0f, 1.0f, 1.0f);
	const Color White(1.0f, 1.0f, 1.0f, 1.0f);
	const Color Black(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Brown(0.64f, 0.164f, 0.164f, 1.0f);
	const Color Grey(0.501f, 0.501f, 0.501f, 1.0f);
	const Color Purple(0.501f, 0.0f, 0.501f, 1.0f);
	const Color Indigo(0.294f, 0.0f, 0.509f, 1.0f);
	const Color Yellow(1.0f, 1.0f, 0.0f, 1.0f);
	const Color Turquoise(0.250f, 0.878f, 0.815f, 1.0f);
	const Color Maroon(0.501f, 0.0f, 0.0f, 1.0f);
	
	Color::Color()
		:r(0.0f), g(0.0f), b(0.0f), a(0.0f){
	}

	Color::Color(float red, float green, float blue, float alpha)
		:r(red), g(green), b(blue), a(alpha)
	{
	}

	
	Color::Color(int red, int green, int blue, int alpha)
		:r(static_cast<float>(red) * 0.0039215f), g(static_cast<float>(green) * 0.0039215f),
		b(static_cast<float>(blue) * 0.0039215f), a(static_cast<float>(alpha) * 0.0039215f)
	{
	}

	Color::Color(const Color& col)
		:r(col.r), g(col.g), b(col.b), a(col.a)
	{
	}

	void Color::operator=(const Color& col)
	{
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
	}
}


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

	float Vec2::Magnitude() const
	{
		return sqrt((x * x) + (y * y));	
	}


	float Vec2::MagnitudeSquared() const
	{
		return (x * x) + (y * y);	
	}

	void Vec2::Normalize()
	{
		float len = Magnitude();
		operator/=(len);
	}

	class Vec2 Vec2::GetNormalized() const
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

	float Vec2::Distance(const Vec2& v)
	{
		return (*this - v).Magnitude();
	}

	float Vec2::DistanceSquared(const Vec2& v)
	{
		return (*this - v).MagnitudeSquared();
	}

	Vec2 Vec2::operator+(const Vec2& v) const
	{
		return Vec2(this->x + v.x, this->y + v.y);
	}

	Vec2 Vec2::operator-(const Vec2& v) const
	{
		return Vec2(this->x - v.x, this->y - v.y);
	}

	Vec2 Vec2::operator*(const float num) const
	{
		return Vec2(this->x * num, this->y * num);
	}

	Vec2 Vec2::operator/(const float num) const
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

	Vec3 Vec3::operator+(const Vec3& v) const
	{
		return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vec3 Vec3::operator-(const Vec3& v) const
	{
		return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	Vec3 Vec3::operator*(const float num) const
	{
		return Vec3(this->x * num, this->y * num, this->z * num);
	}

	Vec3 Vec3::operator/(const float num) const
	{
		float mul = 1.0f / num;
		return Vec3(this->x * mul, this->y * mul, this->z * mul);
	}

	float Vec3::Magnitude() const
	{
		return sqrt((x * x) + (y * y) + (z * z));	
	}

	float Vec3::MagnitudeSquared() const
	{
		return (x * x) + (y * y) + (z * z);	
	}

	void Vec3::Normalize()
	{
		float len = Magnitude();
		operator/=(len);
	}

	Vec3 Vec3::GetNormalized() const
	{
		Vec3 newVec(this->x, this->y, this->z);
		newVec.Normalize();
		return newVec;
	}

	Vec3 Vec3::Project(const Vec3& b) const
	{
		return (b * (Dot(*this,b) / Dot(b, b)));
	}

	Vec3 Vec3::Reject(const Vec3& b) const
	{
		return (*this - b * (Dot(*this,b) / Dot(b, b)));
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

	Vec3 Vec3::Cross(const Vec3& s) const
	{
		return Vec3(y * s.z - z * s.y, z * s.x - x * s.z, x * s.y - y * s.x);
	}

	float Vec3::Distance(const Vec3& v)
	{
		return (*this - v).Magnitude();
	}

	float Vec3::DistanceSquared(const Vec3& v)
	{
		return (*this - v).MagnitudeSquared();
	}

	Vec4::Vec4()
		:x(0.0f), y(0.0f), z(0.0f), t(0.0f)
	{
	}

	Vec4::Vec4(float num)
		:x(num), y(num), z(num), t(num)
	{
	}

	Vec4::Vec4(float v1, float v2, float v3, float v4)
		:x(v1), y(v2), z(v3), t(v4)
	{
	}

	Vec4::Vec4(const Vec4& v)
		:x(v.x), y(v.y), z(v.z), t(v.t)
	{
	}

	Vec4::Vec4(Vec4&& v) noexcept
		:x(std::move(v.x)), y(std::move(v.y)), z(std::move(v.z)), t(std::move(v.t))
	{
	}

	void Vec4::Set(float n)
	{
		x = n;
		y = n;
		z = n;
		t = n;
	}

	void Vec4::Set(float v1, float v2, float v3, float v4)
	{
		x = v1;
		y = v2;
		z = v3;
		t = v4;
	}

	void Vec4::operator=(const Vec4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		t = v.t;
	}

	void Vec4::operator=(Vec4&& v) noexcept
	{
		x = std::move(v.x);
		y = std::move(v.y);
		z = std::move(v.z);
		t = std::move(v.t);
	}

	void Vec4::operator+=(const Vec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		t += v.t;
	}

	void Vec4::operator-=(const Vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		t -= v.t;
	}

	void Vec4::operator*=(const float mul)
	{
		x *= mul;
		y *= mul;
		z *= mul;
		t *= mul;
	}

	void Vec4::operator/=(const float num)
	{
		float mul = 1.0f / num;
		x *= mul;
		y *= mul;
		z *= mul;
		t *= mul;
	}

	float Vec4::Magnitude() const
	{
		return sqrt(x*x + y*y + z*z + t*t);
	}

	float Vec4::MagnitudeSquared() const
	{
		return x*x + y*y + z*z + t*t;
	}

	void Vec4::Normalize()
	{
		float len = Magnitude();
		operator/=(len);
	}

	Vec4 Vec4::GetNormalized() const
	{
		Vec4 newVec(x, y, z, t);
		newVec.Normalize();
		return newVec;
	}

	float Vec4::Distance(const Vec4& v)
	{
		return (*this - v).Magnitude();
	}

	float Vec4::DistanceSquared(const Vec4& v)
	{
		return (*this - v).MagnitudeSquared();
	}

	class Vec4 Vec4::operator+(const Vec4& v) const
	{
		return Vec4(x + v.x, y + v.y, z + v.z, t + v.t);
	}

	class Vec4 Vec4::operator-(const Vec4& v) const
	{
		return Vec4(x - v.x, y - v.y, z - v.z, t - v.t);
	}

	class Vec4 Vec4::operator*(const float num) const
	{
		return Vec4(x * num, y * num, z * num, t * num);
	}

	class Vec4 Vec4::operator/(const float num) const
	{
		float mul = 1.0f / num;
		return Vec4(x * mul, y * mul, z * mul, t * mul);
	}

	const Color Color::red(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::green(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::blue(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::orange(1.0f, 0.64f, 0.0f, 1.0f);
	const Color Color::cyan(0.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::magenta(1.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::white(1.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::black(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::brown(0.64f, 0.164f, 0.164f, 1.0f);
	const Color Color::grey(0.501f, 0.501f, 0.501f, 1.0f);
	const Color Color::purple(0.501f, 0.0f, 0.501f, 1.0f);
	const Color Color::indigo(0.294f, 0.0f, 0.509f, 1.0f);
	const Color Color::yellow(1.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::turquoise(0.250f, 0.878f, 0.815f, 1.0f);
	const Color Color::maroon(0.501f, 0.0f, 0.0f, 1.0f);
	
	Color::Color()
		:r(0.0f), g(0.0f), b(0.0f), a(0.0f){
	}

	Color::Color(float red, float green, float blue, float alpha)
		:r(red), g(green), b(blue), a(alpha)
	{
		Color::red.green;
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


#ifndef OYUN_VECTOR_H__
#define OYUN_VECTOR_H__

#include <ostream>
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
		float x,y;
		Vec2();
		explicit Vec2(float num);
		Vec2(float v1, float v2);
		Vec2(const Vec2 & v);
		Vec2(Vec2&& v) noexcept;
		void Set(float x);
		void Set(float x, float y);
		void operator= (const Vec2& v);
		void operator=(Vec2&& v) noexcept;		
		void operator+=(const Vec2& v);
		void operator-=(const Vec2&v);
		void operator*=(const float num);
		void operator/=(const float num);
		Vec2 operator+(const Vec2& v) const;
		Vec2 operator-(const Vec2& v) const;
		Vec2 operator*(const float num) const;
		Vec2 operator/(const float num) const;
		inline float Magnitude() const;
		inline float MagnitudeSquared() const;
		void Normalize();
		Vec2 GetNormalized() const;
		
		inline static float Dot(const Vec2& f, const Vec2& s); 
		inline float Dot(const Vec2& v);

		float Distance(const Vec2& v);
		float DistanceSquared(const Vec2& v);
	};



	class OYUN_API Vec3
	{

	public:
		float x, y, z;

		Vec3();
		explicit Vec3(float num);
		Vec3(float v1, float v2, float v3);
		Vec3(const Vec3 & v);
		Vec3(Vec3&& v) noexcept;
		void Set(float x);
		void Set(float x, float y, float z);
		void operator= (const Vec3& v);
		void operator=(Vec3&& v) noexcept;		
		void operator+=(const Vec3& v);
		void operator-=(const Vec3&v);
		void operator*=(const float num);
		void operator/=(const float num);
		Vec3 operator+(const Vec3& v) const;
		Vec3 operator-(const Vec3& v) const;
		Vec3 operator*(const float num) const;
		Vec3 operator/(const float num) const;
		inline float Magnitude() const;
		inline float MagnitudeSquared() const;
		void Normalize();
		Vec3 GetNormalized() const;

		Vec3 Project(const Vec3& m) const;
		Vec3 Reject(const Vec3& m) const;

		inline static float Dot(const Vec3& f, const Vec3& s); 
		inline float Dot(const Vec3& v);

		inline static Vec3 Cross(const Vec3& f, const Vec3& s);
		inline Vec3 Cross(const Vec3& v) const;

		float Distance(const Vec3& v);
		float DistanceSquared(const Vec3& v);
		
	};

	class OYUN_API Vec4
	{

	public:
		float x, y, z, t;

		Vec4();
		explicit Vec4(float num);
		Vec4(float v1, float v2, float v3, float v4);
		Vec4(const Vec4 & v);
		Vec4(Vec4&& v) noexcept;
		void Set(float x);
		void Set(float v1, float v2, float v3, float v4);
		void operator= (const Vec4& v);
		void operator=(Vec4&& v) noexcept;		
		void operator+=(const Vec4& v);
		void operator-=(const Vec4&v);
		void operator*=(const float num);
		void operator/=(const float num);
		Vec4 operator+(const Vec4& v) const;
		Vec4 operator-(const Vec4& v) const;
		Vec4 operator*(const float num) const;
		Vec4 operator/(const float num) const;
		inline float Magnitude() const;
		inline float MagnitudeSquared() const;
		void Normalize();
		Vec4 GetNormalized() const;

		float Distance(const Vec4& v);
		float DistanceSquared(const Vec4& v);
	
	};

	class OYUN_API Color
	{
		public:

		float r,g,b,a;

		Color();
		Color(float red, float green, float blue, float alpha);
		
		/// @brief red green blue and alpha [0-255] integer
		Color(int red, int green, int blue, int alpha);

		Color(const Color& col);

		Color(Color&& col) = delete;

		void operator= (const Color& col);

		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color orange;
		static const Color cyan;
		static const Color magenta;
		static const Color black;
		static const Color white;
		static const Color brown;
		static const Color grey;
		static const Color purple;
		static const Color indigo;
		static const Color yellow;
		static const Color turquoise;
		static const Color maroon;
		
	};


	
	OYUN_API std::ostream& operator<<(std::ostream &strm, const Vec2 &a)
	{
	  return strm << "Vector2D(" << a.x <<", " << a.y << ")";
	}
	
	OYUN_API std::ostream& operator<<(std::ostream &strm, const Vec3 &a)
	{
	  return strm << "Vec3(" << a.x <<", " << a.y<<", "<< a.z << ")";
	}

	OYUN_API std::ostream& operator<<(std::ostream &strm, const Color &a)
	{
	  return strm << "Color(" << a.r <<", " << a.g<<", "<< a.b <<", "<< a.a<< ")";
	}

	OYUN_API std::ostream& operator<<(std::ostream &strm, const Vec4 &a)
	{
	  return strm << "Vec4(" << a.x <<", " << a.y<<", "<< a.z <<", "<< a.t << ")";
	}


	

	
}
#endif //OYUN_VECTOR_H__
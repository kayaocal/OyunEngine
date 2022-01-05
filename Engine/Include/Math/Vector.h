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
		Vec2 operator+(const Vec2& v);
		Vec2 operator-(const Vec2& v);
		Vec2 operator*(const float num);
		Vec2 operator/(const float num);
		inline float Magnitude();
		inline float MagnitudeSquared();
		void Normalize();
		Vec2 GetNormalized();

		inline static float Dot(const Vec2& f, const Vec2& s); 
		inline float Dot(const Vec2& v);
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
		Vec3 operator+(const Vec3& v);
		Vec3 operator-(const Vec3& v);
		Vec3 operator*(const float num);
		Vec3 operator/(const float num);
		inline float Magnitude();
		inline float MagnitudeSquared();
		void Normalize();
		Vec3 GetNormalized();

		inline static float Dot(const Vec3& f, const Vec3& s); 
		inline float Dot(const Vec3& v);

		inline static Vec3 Cross(const Vec3& f, const Vec3& s);
		inline Vec3 Cross(const Vec3& v);
	};

	template<typename T>
	class OYUN_API Vector4D
	{

	public:

		T x, y, z, t;
		
		Vector4D()	{	}
		
		Vector4D(T num)
			: x(num), y(num), z(num), t(num)
		{
		}
		
		Vector4D(T v1, T v2, T v3, T v4)
			:x(v1), y(v2), z(v3), t(v4)
		{
		}

		Vector4D(const Vector4D<T> & v)
			: x(v.x), y(v.y), z(v.z), t(v.t)
		{
		}

		Vector4D(Vector4D<T>&& v) noexcept
			:x(std::move(v.x)), y(std::move(v.y)), z(std::move(v.z)), t(std::move(v.t))
		{
		}

		void Set(T x)
		{
			this->x = x;
			this->y = x;
			this->z = x;
			this->t = x;
		}
		void Set(T x, T y, T z, T t)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->t= t;
		}

		void operator= (const Vector4D<T>& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->t = v.t;
		}

		void operator=(Vector4D<T>&& v) noexcept
		{
			this->x = std::move(v.x);
			this->y = std::move(v.y);
			this->z = std::move(v.z);
			this->t = std::move(v.t);
		}
		
		void operator+=(const Vector4D<T>& v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
			this->t += v.t;
		}
		
		void operator-=(const Vector4D<T>&v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
			this->t -= v.t;
		}

		void operator*=(const T num)
		{
			this->x *= num;
			this->y *= num;
			this->z *= num;
			this->t *= num;
		}

		void operator/=(const T num)
		{
			this->x /= num;
			this->y /= num;
			this->z /= num;
			this->t /= num;
		}

		void operator/=(const float num)
		{
			float mul = 1.0f / num;
			this->operator*=(mul);
		}
		
		Vector4D<T> operator+(const Vector4D<T>& v)
		{
			return Vector4D<T>(this->x + v.x, this->y + v.y, this->z + v.z, this->t + v.t);
		}
		
		Vector4D<T> operator-(const Vector4D<T>& v)
		{
			return Vector4D<T>(this->x - v.x, this->y - v.y, this->z - v.z, this->t - v.t);
		}
		
		Vector4D<T> operator*(const T num)
		{
			return Vector4D<T>(this->x * num, this->y * num, this->z * num, this->t * num);
		}
		
		Vector4D<T> operator/(const T num)
		{
			return Vector4D<T>(this->x / num, this->y / num, this->z / num, this->t / num);
		}

		Vector4D<T> operator/(const float num)
		{
			float mul = 1.0f / num;
			return Vector4D<T>(this->x * mul, this->y * mul, this->z * mul, this->t * mul);
		}

		inline T Magnitude()
		{
			return sqrt((x * x) + (y * y) + (z * z) + (t * t));	
		}

		inline T MagnitudeSquared()
		{
			return (x * x) + (y * y) + (z * z) + (t * t);	
		}

		void Normalize()
		{
			T len = Magnitude();
			operator/=(len);
		}

		
		Vector4D<T> GetNormalized()
		{
			Vector4D<T> newVec(this->x, this->y, this->z, this->t);
			newVec.Normalize();
			return newVec;
		}

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
		
	};

	OYUN_API extern const Color Red;
	OYUN_API extern const Color Green;
	OYUN_API extern const Color Blue;
	OYUN_API extern const Color Orange;
	OYUN_API extern const Color Cyan;
	OYUN_API extern const Color Magenta;
	OYUN_API extern const Color Black;
	OYUN_API extern const Color White;
	OYUN_API extern const Color Brown;
	OYUN_API extern const Color Grey;
	OYUN_API extern const Color Purple;
	OYUN_API extern const Color Indigo;
	OYUN_API extern const Color Yellow;
	OYUN_API extern const Color Turquoise;
	OYUN_API extern const Color Maroon;
	
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

	template<typename  T>
	OYUN_API std::ostream& operator<<(std::ostream &strm, const Vector4D<T> &a)
	{
	  return strm << "Vector4D(" << a.x <<", " << a.y<<", "<< a.z <<", "<< a.t << ")";
	}


	using Vec4 = Vector4D<float>;
	

	
}
#endif //OYUN_VECTOR_H__
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
	
	template<typename T>
	class OYUN_API Vector2D
	{

	public:

		T x, y;

		Vector2D()	{	}
		
		Vector2D(T num)
			: x(num), y(num)
		{
		}
		
		Vector2D(T v1, T v2)
			:x(v1), y(v2)
		{
		}

		Vector2D(const Vector2D<T> & v)
			: x(v.x), y(v.y)
		{
		}

		Vector2D(Vector2D<T>&& v) noexcept
			:x(std::move(v.x)), y(std::move(v.y))
		{
		}

		void Set(T x)
		{
			this->x = x;
			this->y = x;
		}
		void Set(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		void operator= (const Vector2D<T>& v)
		{
			this->x = v.x;
			this->y = v.y;
		}

		void operator=(Vector2D<T>&& v) noexcept
		{
			this->x = std::move(v.x);
			this->y = std::move(v.y);
		}
		
		void operator+=(const Vector2D<T>& v)
		{
			this->x += v.x;
			this->y += v.y;
		}
		
		void operator-=(const Vector2D<T>&v)
		{
			this->x -= v.x;
			this->y -= v.y;
		}

		void operator*=(const T num)
		{
			this->x *= num;
			this->y *= num;
		}

		void operator/=(const T num)
		{
			this->x /= num;
			this->y /= num;
		}
		
		Vector2D<T> operator+(const Vector2D<T>& v)
		{
			return Vector2D<T>(this->x + v.x, this->y + v.y);
		}
		
		Vector2D<T> operator-(const Vector2D<T>& v)
		{
			return Vector2D<T>(this->x - v.x, this->y - v.y);
		}
		
		Vector2D<T> operator*(const T num)
		{
			return Vector2D<T>(this->x * num, this->y * num);
		}
		
		Vector2D<T> operator/(const T num)
		{
			return Vector2D<T>(this->x / num, this->y / num);
		}

		inline T Magnitude()
		{
			return sqrt((x * x) + (y * y));	
		}

		inline T MagnitudeSquared()
		{
			return (x * x) + (y * y);	
		}

		void Normalize()
		{
			T len = Magnitude();
			operator/=(len);
		}

		
		Vector2D<T> GetNormalized()
		{
			Vector2D<T> newVec(this->x, this->y);
			newVec.Normalize();
			return newVec;
		}

	};



	template<typename T>
	class OYUN_API Vector3D
	{

	public:

		T x, y, z;

		Vector3D()	{	}
		
		Vector3D(T num)
			: x(num), y(num), z(num)
		{
		}
		
		Vector3D(T v1, T v2, T v3)
			:x(v1), y(v2), z(v3)
		{
		}

		Vector3D(const Vector3D<T> & v)
			: x(v.x), y(v.y), z(v.z)
		{
		}

		Vector3D(Vector3D<T>&& v) noexcept
			:x(std::move(v.x)), y(std::move(v.y)), z(std::move(v.z))
		{
		}

		void Set(T x)
		{
			this->x = x;
			this->y = x;
			this->z = x;
		}
		void Set(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		void operator= (const Vector3D<T>& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		void operator=(Vector3D<T>&& v) noexcept
		{
			this->x = std::move(v.x);
			this->y = std::move(v.y);
			this->z = std::move(v.z);
		}
		
		void operator+=(const Vector3D<T>& v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}
		
		void operator-=(const Vector3D<T>&v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}

		void operator*=(const T num)
		{
			this->x *= num;
			this->y *= num;
			this->z *= num;
		}

		void operator/=(const T num)
		{
			this->x /= num;
			this->y /= num;
			this->z /= num;
		}

		void operator/=(const float num)
		{
			float mul = 1.0f / num;
			this->operator*=(mul);
		}
		
		Vector3D<T> operator+(const Vector3D<T>& v)
		{
			return Vector3D<T>(this->x + v.x, this->y + v.y, this->z + v.z);
		}
		
		Vector3D<T> operator-(const Vector3D<T>& v)
		{
			return Vector3D<T>(this->x - v.x, this->y - v.y, this->z - v.z);
		}
		
		Vector3D<T> operator*(const T num)
		{
			return Vector3D<T>(this->x * num, this->y * num, this->z * num);
		}
		
		Vector3D<T> operator/(const T num)
		{
			return Vector3D<T>(this->x / num, this->y / num, this->z / num);
		}

		Vector3D<T> operator/(const float num)
		{
			float mul = 1.0f / num;
			return Vector3D<T>(this->x * mul, this->y * mul, this->z * mul);
		}

		inline T Magnitude()
		{
			return sqrt((x * x) + (y * y) + (z * z));	
		}

		inline T MagnitudeSquared()
		{
			return (x * x) + (y * y) + (z * z);	
		}

		void Normalize()
		{
			T len = Magnitude();
			operator/=(len);
		}

		
		Vector3D<T> GetNormalized()
		{
			Vector3D<T> newVec(this->x, this->y, this->z);
			newVec.Normalize();
			return newVec;
		}

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

	template<typename  T>
	std::ostream& operator<<(std::ostream &strm, const Vector2D<T> &a)
	{
	  return strm << "Vector2D(" << a.x <<", " << a.y << ")";
	}
	
	template<typename  T>
	std::ostream& operator<<(std::ostream &strm, const Vector3D<T> &a)
	{
	  return strm << "Vector3D(" << a.x <<", " << a.y<<", "<< a.z << ")";
	}

	template<typename  T>
	std::ostream& operator<<(std::ostream &strm, const Vector4D<T> &a)
	{
	  return strm << "Vector4D(" << a.x <<", " << a.y<<", "<< a.z <<", "<< a.t << ")";
	}

	using Vec2 = Vector2D<float>;
	using Vec2i = Vector2D<int>;
	
	using Vec3 = Vector3D<float>;
	using Vec3i = Vector3D<int>;
	
	using Vec4 = Vector4D<float>;
	

	
}
#endif //OYUN_VECTOR_H__
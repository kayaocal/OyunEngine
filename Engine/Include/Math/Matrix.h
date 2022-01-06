#ifndef OYUN_MATRIX_H__
#define OYUN_MATRIX_H__
#include "Vector.h"

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
    struct OYUN_API Mat3
    {
        
        Mat3();

        Mat3(float n00, float n01, float n02,
            float n10, float n11, float n12,
            float n20, float n21, float n22);
                

        Mat3(const Vec3& a, const Vec3& b, const Vec3& c);
        Mat3(const Mat3& m);


        static const Mat3 identity;

        const float& operator()(int i, int j) const;

        Mat3 operator*(float v) const;
        Mat3 operator*(const Mat3& v) const;
        Vec3 operator*(const Vec3& v);
        Mat3 operator+(const Mat3& v);
        Mat3 operator-(const Mat3& v);

        float Determinant(const Mat3& m) const;
        private:
        float n[3][3];
    

    };

    struct Mat4
    {
        Mat4();
        Mat4(float n00, float n01, float n02, float n03,
             float n10, float n11, float n12, float n13,
             float n20, float n21, float n22, float n23,
             float n30, float n31, float n32, float n33);
                

        Mat4(const Mat4& m);

        static const Mat4 identity;

        const float& operator()(int i, int j) const;

        Mat4 operator*(float v);
        Mat4 operator*(const Mat4& v);
        Vec4 operator*(const Vec4& v);
        Mat4 operator+(const Mat4& v);
        Mat4 operator-(const Mat4& v);
    
    private:
        float n[4][4];
    };
    
}


#endif //OYUN_MATRIX__
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

        Mat3() = default;

        Mat3(float n00, float n01, float n02,
            float n10, float n11, float n12,
            float n20, float n21, float n22);
                

        Mat3(const Vec3& a, const Vec3& b, const Vec3& c);
        Mat3(const Mat3& m);

        const float& operator()(int i, int j) const;

        Mat3 operator*(float v);
        Mat3 operator*(const Mat3& v);
        Vec3 operator*(const Vec3& v);
        Mat3 operator+(const Mat3& v);
        Mat3 operator-(const Mat3& v);

        private:
        float n[3][3];


    };

    
}


#endif //OYUN_MATRIX__
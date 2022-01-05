#include "Math/Matrix.h"

namespace Oyun
{
    
    Mat3::Mat3(float n00, float n01, float n02,
        float n10, float n11, float n12,
        float n20, float n21, float n22)
        : n{n00,n01,n02,n10,n11,n12,n20,n21,n22}
    {
    }

    Mat3::Mat3(const Vec3& a, const Vec3& b, const Vec3& c)
        : n{a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z}
    {
        
    }

    Mat3::Mat3(const Mat3& m)
        :n{ m(0,0), m(0,1), m(0,2),
            m(1,0), m(1,1), m(1,2),
            m(2,0), m(2,1), m(2,2),
        }
    {

    }

    const float& Mat3::operator()(int i, int j) const
    {
        return n[i][j];
    }

    Mat3 Mat3::operator*(float v)
    {
        return Mat3(n[0][0] * v, n[0][1] * v, n[0][2] * v,
                    n[1][0] * v, n[1][1] * v, n[1][2] * v,
                    n[2][0] * v, n[2][1] * v, n[2][2] * v);
    }

    Mat3 Mat3::operator*(const Mat3& v)
    {
        return Mat3(    n[0][0] * v(0,0) + n[0][1] * v(1,0) + n[0][2] * v(2,0),
                        n[0][0] * v(0,1) + n[0][1] * v(1,1) + n[0][2] * v(2,1),
                        n[0][0] * v(0,2) + n[0][1] * v(1,2) + n[0][2] * v(2,2),
                        n[1][0] * v(0,0) + n[1][1] * v(1,0) + n[1][2] * v(2,0),
                        n[1][0] * v(0,1) + n[1][1] * v(1,1) + n[1][2] * v(2,1),
                        n[1][0] * v(0,2) + n[1][1] * v(1,2) + n[1][2] * v(2,2),
                        n[2][0] * v(0,0) + n[2][1] * v(1,0) + n[2][2] * v(2,0),
                        n[2][0] * v(0,1) + n[2][1] * v(1,1) + n[2][2] * v(2,1),
                        n[2][0] * v(0,2) + n[2][1] * v(1,2) + n[2][2] * v(2,2)
            );
    }

    Vec3 Mat3::operator*(const Vec3& v)
    {
        return Vec3(n[0][0] * v.x + n[0][1] * v.y + n[0][2] * v.z,
                    n[1][0] * v.x + n[1][1] * v.y + n[1][2] * v.z,
                    
                    n[2][0] * v.x + n[2][1] * v.y + n[2][2] * v.z);
    }

    Mat3 Mat3::operator+(const Mat3& v)
    {
         return Mat3(n[0][0] + v(0, 0), n[0][1] + v(0, 1), n[0][2] + v(0, 2),
                     n[1][0] + v(1, 0), n[1][1] + v(1, 1), n[1][2] + v(1, 2),
                     n[2][0] + v(2, 0), n[2][1] + v(2, 1), n[2][2] + v(2, 2));
    }

    Mat3 Mat3::operator-(const Mat3& v)
    {
        return Mat3( n[0][0] - v(0, 0), n[0][1] - v(0, 1), n[0][2] - v(0, 2),
                     n[1][0] - v(1, 0), n[1][1] - v(1, 1), n[1][2] - v(1, 2),
                     n[2][0] - v(2, 0), n[2][1] - v(2, 1), n[2][2] - v(2, 2));
    }
}


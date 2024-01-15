#pragma once
#include <cmath>
#include <iostream>

class Vector3
{
public:
    double x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(double pX, double pY, double pZ) : x(pX), y(pY), z(pZ) {}

    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    double operator[](int i) const { return i == 0 ? x : (i == 1 ? y : z); }
    double& operator[](int i) { return i == 0 ? x : (i == 1 ? y : z); }

    Vector3& operator+=(const Vector3& rVec)
    {
        x += rVec.x; y += rVec.y; z += rVec.z;
        return *this;
    }

    Vector3& operator*=(double t)
    {
        x *= t; y *= t; z *= t;
        return *this;
    }

    Vector3& operator/=(double t)
    {
        x /= t; y *= t; z *= t;
        return *this;
    }

    double Length() const
    {
        return sqrt(SquaredLength());
    }

    double SquaredLength() const
    {
        return x * x + y * y + z * z;
    }
};

//Alias for Vector3 to increase code readability
using Position = Vector3;

inline std::ostream& operator<<(std::ostream& rOut, const Vector3& rV)
{
    return rOut << rV.x << ' ' << rV.y << ' ' << rV.z << std::endl;
}

inline Vector3 operator+(const Vector3& rLeft, const Vector3& rRight)
{
    return Vector3(rLeft.x + rRight.x, rLeft.y + rRight.y, rLeft.z + rRight.z);
}

inline Vector3 operator-(const Vector3& rLeft, const Vector3& rRight)
{
    return Vector3(rLeft.x - rRight.x, rLeft.y - rRight.y, rLeft.z - rRight.z);
}

inline Vector3 operator*(const Vector3& rLeft, const Vector3& rRight)
{
    return Vector3(rLeft.x * rRight.x, rLeft.y * rRight.y, rLeft.z * rRight.z);
}

inline Vector3 operator*(const Vector3& rLeft, double scalar)
{
    return Vector3(rLeft.x * scalar, rLeft.y * scalar, rLeft.z * scalar);
}

inline Vector3 operator*(double scalar, const Vector3& rRight)
{
    return rRight * scalar;
}

inline Vector3 operator/(Vector3 vector, double scalar)
{
    return (1 / scalar) * vector;
}

inline double Dot(const Vector3& rLeft, const Vector3 rRight)
{
    return rLeft.x * rRight.x
        + rLeft.y * rRight.y
        + rLeft.z * rRight.z;
}

inline Vector3  Cross(const Vector3& rLeft, const Vector3& rRight)
{
    return Vector3(rLeft.y * rRight.z - rLeft.z * rRight.y,
        rLeft.z * rRight.x - rLeft.x * rRight.z,
        rLeft.x * rRight.y - rLeft.y * rRight.x);
}

inline Vector3 Unit(Vector3 vector)
{
    return vector / vector.Length();
}

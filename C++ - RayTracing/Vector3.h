#pragma once
#include <cmath>
#include <iostream>
#include "Utility.h"


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

    static Vector3 Random()
    {
        return Vector3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    static Vector3 Random(double min, double max)
    {
        return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    bool NearZero() const
    {
        double s = 1e-18;
        return fabs(x < s) && fabs(y < s) && fabs(z < s);
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

inline Vector3 Unit(const Vector3& vector)
{
    return vector / vector.Length();
}

inline Position RandomInUnitSphere()
{
    while (true)
    {
        Position position = Vector3::Random(-1, 1);
        if (position.SquaredLength() < 1) return position;
    }
}

inline Vector3 RandomInUnitDisk()
{
    while (true)
    {
        Vector3 position = Vector3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
        if (position.SquaredLength() < 1)
            return position;
    }
}


inline Vector3 RandomUnitVector()
{
    return Unit(RandomInUnitSphere());
}

inline Vector3 RandomOnHemisphere(const Vector3& normal)
{
    Vector3 onUnitSphere = RandomUnitVector();
    //If in the same hemisphere as the normal
    if (Dot(onUnitSphere, normal) > 0.0)
    {
        return onUnitSphere;
    }
    return -onUnitSphere;
}

inline Vector3 Reflect(const Vector3& direction, const Vector3& normal)
{
    return direction - 2 * Dot(direction, normal) * normal;
}

inline Vector3 Refract(const Vector3& unitVector, const Vector3& normal, double refractionRatio)
{
    double cosTheta = fmin(Dot(-unitVector, normal), 1.0);
    Vector3 rayOutPerpendicular = refractionRatio * (unitVector + cosTheta * normal);
    Vector3 rayOutParallel = -sqrt(fabs(1.0 - rayOutPerpendicular.SquaredLength())) * normal;
    return rayOutPerpendicular + rayOutParallel;
}




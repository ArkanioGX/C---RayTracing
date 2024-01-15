#pragma once
#include "Vector3.h"

class Ray
{
private:
    Position mOrigin;
    Vector3 mDirection;
public:
    Ray() {}
    Ray(const Position& from, const Vector3& towards) : mOrigin(from), mDirection(towards) {}

    Position GetOrigin() const { return mOrigin; }
    Vector3 GetDirection() const { return mDirection; }

    Position At(double time) const
    {
        return mOrigin + time * mDirection;
    }
};

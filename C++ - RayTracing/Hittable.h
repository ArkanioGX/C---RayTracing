#pragma once
#include "Ray.h"
#include "Interval.h"

class HitInfo
{
public:
	Position coordinates;
	Vector3 normal;
	double time;
	bool frontFace;

	void SetFaceNormal(const Ray& rRay, const Vector3& outwardNormal)
	{
		//NOTE : The outwardNormal vector should be unit length
		frontFace = Dot(rRay.GetDirection(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}

};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const = 0;

};

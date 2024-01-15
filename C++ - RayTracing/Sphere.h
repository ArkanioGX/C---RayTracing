#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
private:
	Position mCenter;
	double mRadius;
public:
	Sphere(Position center, double radius) :mCenter(center), mRadius(radius) {}
	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;

};

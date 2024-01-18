#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
private:
	Position mCenter;
	double mRadius;
	shared_ptr<Material> material;
public:
	Sphere(Position center, double radius, shared_ptr<Material> mat) :mCenter(center), mRadius(radius), material(mat) {}
	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;

};

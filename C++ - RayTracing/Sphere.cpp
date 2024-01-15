#include "Sphere.h"

bool Sphere::Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const
{
    Vector3 oC = rRay.GetOrigin() - mCenter;
    double a = rRay.GetDirection().SquaredLength();
    double halfB = Dot(oC, rRay.GetDirection());
    double c = oC.SquaredLength() - mRadius * mRadius;

    double discriminant = halfB * halfB - a * c;
    if (discriminant < 0) return false;
    double sqrtDiscriminant = sqrt(discriminant);

    // Find the nearest root withing the min max time frame
    double root = (-halfB - sqrtDiscriminant) / a;
    if (!rayTime.Surrounds(root)) {
        root = (-halfB + sqrtDiscriminant) / a;
        if (!rayTime.Surrounds(root))
            return false;
    }


    hitInfo.time = root;
    hitInfo.coordinates = rRay.At(hitInfo.time);
    Vector3 outwardNormal = (hitInfo.coordinates - mCenter) / mRadius;
    hitInfo.SetFaceNormal(rRay, outwardNormal);

    return true;
}

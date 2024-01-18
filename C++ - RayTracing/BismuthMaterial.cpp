#include "BismuthMaterial.h"
#include "Hittable.h"

bool BismuthMaterial::Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	Vector3 reflected = Reflect(Unit(rRayIn.GetDirection()), hitInfo.normal);
	scattered = Ray(hitInfo.coordinates, reflected + fuzz * RandomUnitVector());
	attenuation = albedo;
	return Dot(scattered.GetDirection(), hitInfo.normal) > 0;
}

#include "DialectricMaterial.h"
#include "Hittable.h"

bool DialectricMaterial::Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);
	double refractionRatio = hitInfo.frontFace ? (1.0 / refractionIndex) : refractionIndex;

	Vector3 unitDirection = Unit(rRayIn.GetDirection());
	double cosTheta = fmin(Dot(-unitDirection, hitInfo.normal), 1.0);
	double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0;
	Vector3 direction;

	if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble()) direction = Reflect(unitDirection, hitInfo.normal);
	else direction = Refract(unitDirection, hitInfo.normal, refractionRatio);


	scattered = Ray(hitInfo.coordinates, direction);
	return true;
}

double DialectricMaterial::Reflectance(double cosine, double pRefractionIndex)
{
	//Shlick approximation of reflectance
	double reflectance = (1 - pRefractionIndex) / (1 + pRefractionIndex);
	reflectance *= reflectance;
	return reflectance + (1 - reflectance) * pow((1 - cosine), 5);
}


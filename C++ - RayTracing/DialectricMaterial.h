#pragma once
#include "Material.h"

class DialectricMaterial : public Material
{
private:
	double refractionIndex;
	

public:
	DialectricMaterial(double refIndex) : refractionIndex(refIndex) {}
	bool Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
	static double Reflectance(double cosine, double pRefractionIndex);
};

#pragma once
#include "Material.h"

class LambertianMaterial : public Material
{
private:
	Color albedo;
public:
	LambertianMaterial(const Color& baseColor) : albedo(baseColor) {}

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
};

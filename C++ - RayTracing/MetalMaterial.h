#pragma once
#include "Material.h"

class MetalMaterial :public Material
{
private:
	Color albedo;
	double fuzz;
public:
	MetalMaterial(const Color& baseColor, double f = 1) : albedo(baseColor), fuzz(f < 1 ? f : 1) {}

	bool Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
};

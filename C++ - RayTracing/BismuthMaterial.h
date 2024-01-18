#pragma once
#include "Material.h"

class BismuthMaterial :public Material
{
private:
	Color albedo;
	double fuzz;
	float chromaPower;

public:
	BismuthMaterial(const Color& baseColor, double f = 1, double cp = 1) : albedo(baseColor), fuzz(f < 1 ? f : 1), chromaPower(cp) {}

	bool Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;

	float getChromaP() { return chromaPower; }
};
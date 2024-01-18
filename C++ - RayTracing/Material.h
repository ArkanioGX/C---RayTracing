#pragma once

#include "Color.h"
#include "Ray.h"

class HitInfo;

class Material
{
public:
	~Material() = default;

	virtual bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const = 0;
};

#pragma once
#include "Color.h"
#include "Hittable.h"

class Camera
{
public:
	Camera() = default;
	Camera(double imageWidth, double ratio, int samplePerPixel = 10) : aspectRatio(ratio), width(imageWidth), sampleCount(samplePerPixel) {}
	void Render(const Hittable& rWorld);
private:
	int height;
	double aspectRatio, width;
	int sampleCount;
	Position center, originPixelLocation;
	Vector3 pixelDeltaX, pixelDeltaY;

	void Initialize();
	Color RayColor(const Ray& rRay, const Hittable& rWorld) const;
	Ray GetRay(int x, int y) const;
	Vector3 PixelSampleSquared() const;

};


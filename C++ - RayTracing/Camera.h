#pragma once
#include "Color.h"
#include "Hittable.h"

class Camera
{
public:
	Camera() = default;
	Camera(double imageWidth, double ratio, int samplePerPixel = 10, int bounces = 10, double vFoV = 90) : aspectRatio(ratio), width(imageWidth), sampleCount(samplePerPixel), maxBounces(bounces), verticalFoV(vFoV) {};
	
	void SetTransform(Vector3 origin = Vector3(0, 0, 0), Vector3 lookAt = Vector3(0, 0, -1), Vector3 upDirection = Vector3(0, 1, 0));
	void SetFocus(double angle = 0, double distance = 10);
	void Render(const Hittable& rWorld);

	
private:
	int height;
	double aspectRatio, width;
	int sampleCount;
	double verticalFoV;
	int maxBounces;
	double defocusAngle, focusDistance;
	Position position, target;
	Vector3 viewUp;
	Vector3 right, up, forward;
	Position center, originPixelLocation;
	Vector3 defocusDiskX, defocusDiskY;
	Vector3 pixelDeltaX, pixelDeltaY;

	void Initialize();
	Color RayColor(const Ray& rRay, int bouncesLeft, const Hittable& rWorld) const;
	Ray GetRay(int x, int y) const;
	Vector3 PixelSampleSquared() const;
	Position DefocusDiskSample() const;
};


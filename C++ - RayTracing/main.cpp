// C++ - RayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Color.h"
#include "Ray.h"
#include "Utility.h"
#include "HittableCollection.h"
#include "Sphere.h"
#include "Camera.h" 

double HitSphere(const Position& rCenter, double radius, const Ray& rRay)
{
    Vector3 oC = rRay.GetOrigin() - rCenter;
    double a = rRay.GetDirection().SquaredLength();
    double halfB = Dot(oC, rRay.GetDirection());
    double c = oC.SquaredLength() - radius * radius;

    double discriminant = halfB * halfB - a * c;

    if (discriminant < 0) return -1.0;

    return (-halfB - sqrt(discriminant)) / a;


}


Color RayColor(const Ray& rRay, const Hittable& rWorld)
{
    HitInfo hitInfo;
    if (rWorld.Hit(rRay, Interval(0, infinity), hitInfo)) {
        return 0.5 * (hitInfo.normal + Color(1, 1, 1));
    }
    Vector3 unitDirection = Unit(rRay.GetDirection());
    double blue = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0.5, 0.7, 1.0);
}



int main()
{
    //Resolution
    double resolution = 16.0 / 9.0;
    int width = 1920, height = static_cast<int>(width / resolution);
    height = std::max(1, height);

    //Viewport
    double viewportHeight = 2;
    double viewportWidth = viewportHeight * (static_cast<double>(width) / height);
    double focalLength = 1;
    Position cameraCenter = Position(0, 0, 0);

    Vector3 viewportX = Vector3(viewportWidth, 0, 0);
    Vector3 viewportY = Vector3(0, -viewportHeight, 0); //We invert Y

    //Delta vector between pixels
    Vector3 pixelDeltaX = viewportX / width;
    Vector3 pixelDeltaY = viewportY / height;

    //Position of the top left pixel
    Vector3 viewportOrigin = cameraCenter - Vector3(0, 0, focalLength)
        - viewportX / 2 - viewportY / 2;

    Vector3 originPixelLocation = viewportOrigin + 0.5 * (pixelDeltaX + pixelDeltaY);

    //World
    HittableCollection world;
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Position(0, -100.5, -1), 100));

    Camera camera(width, resolution,100, 50);
    camera.Render(world);
    return 0;
}






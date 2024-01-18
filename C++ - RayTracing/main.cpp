// C++ - RayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Color.h"
#include "Ray.h"
#include "Utility.h"
#include "HittableCollection.h"
#include "Sphere.h"
#include "Camera.h" 
#include "MetalMaterial.h"
#include "LambertianMaterial.h"
#include "DialectricMaterial.h"
#include "BismuthMaterial.h"
#include <random>

void createRandomScene(HittableCollection* world, int SphereN, bool hasGround);

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





int main()
{
    //Resolution
    double resolution = 16.0 / 9.0;
    int width = 400, height = static_cast<int>(width / resolution);
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

    shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMat = make_shared<DialectricMaterial>(1.5);
    shared_ptr<Material> leftMat = make_shared<MetalMaterial>(Color(0.2, 0.3, 0.5), 1.0);
    shared_ptr<Material> rightMat = make_shared<BismuthMaterial>(Color(0.5, 0.3, 0.2), 1.0, 2);


    world.Add(make_shared<Sphere>(Position(0, -100.5, -1), 100, groundMat));
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5, centerMat));
    world.Add(make_shared<Sphere>(Position(-1.0, 0, -1), 0.5, leftMat));
    world.Add(make_shared<Sphere>(Position(1.0, 0, -1), 0.5, rightMat));

    //createRandomScene(&world, 1, true);



    Camera camera(width, resolution,100, 50);
    camera.Render(world);
    return 0;
}

void createRandomScene(HittableCollection* world, int SphereN, bool hasGround) {

    if (hasGround) {
        shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
        world->Add(make_shared<Sphere>(Position(0, -100.5, -1), 100, groundMat));
    }

    double size = 1 / SphereN;
    for (int i = 0; i < SphereN; i++) {
        int matType = 1 + (rand() % 2);

        float r = (rand() % 256 / 255);
        float g = (rand() % 256 / 255);
        float b = (rand() % 256 / 255);
        shared_ptr<Material> mat;
        switch (matType) {
        case 1:
            mat = make_shared<LambertianMaterial>(Color(r, g, b));
            break;
        case 2:
            mat = make_shared<MetalMaterial>(Color(r, g, b),1);
            break;
        default: break;
        }

        float x = (-127 + rand() % 128 / 128);
        float z = (-127 + rand() % 128 / 128);


        world->Add(make_shared<Sphere>(Position(x, 0, -1), 0.5, mat));
    }
}





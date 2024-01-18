#include "Camera.h"
#include "BismuthMaterial.h"

void Camera::Render(const Hittable& rWorld)
{
    Initialize();
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int y = 0; y < height; y++)
    {
        std::clog << "Progress : " << (y * 100 / height) << " %\n" << std::flush;
        for (int x = 0; x < width; x++)
        {
            Color pixel(0, 0, 0);
            for (int sample = 0; sample < sampleCount; sample++)
            {
                Ray ray = GetRay(x, y);
                pixel += RayColor(ray,maxBounces, rWorld);
            }

            WriteColor(std::cout, pixel, sampleCount);
        }
    }
    std::clog << "Done! You can open your file now :)\n";
}


void Camera::Initialize()
{
    height = static_cast<int>(width / aspectRatio);
    if (height < 1) height = 1;

    center = Position(0, 0, 0);
    double focalLength = 1;
    double viewportHeight = 2;
    double viewportWidth = viewportHeight * (static_cast<double>(width) / height);

    Vector3 viewportX = Vector3(viewportWidth, 0, 0);
    Vector3 viewportY = Vector3(0, -viewportHeight, 0); //We invert Y

    //Delta vector between pixels
    pixelDeltaX = viewportX / width;
    pixelDeltaY = viewportY / height;

    //Position of the top left pixel
    Vector3 viewportOrigin = center - Vector3(0, 0, focalLength)
        - viewportX / 2 - viewportY / 2;

    originPixelLocation = viewportOrigin + 0.5 * (pixelDeltaX + pixelDeltaY);

}

Color Camera::RayColor(const Ray& rRay, int bouncesLeft, const Hittable& rWorld) const
{
    HitInfo hitInfo;
    if (bouncesLeft <= 0) return Color(0, 0, 0);
    if (rWorld.Hit(rRay, Interval(0.001, infinity), hitInfo)) {
        Ray scattered;
        Color attenuation;
        if (hitInfo.material->Scatter(rRay, hitInfo, attenuation, scattered))
        {
            if (std::dynamic_pointer_cast<BismuthMaterial>(hitInfo.material) != nullptr) {
                Color BismuthColor = normalColor(hitInfo.normal);
                shared_ptr<BismuthMaterial> bm = std::dynamic_pointer_cast<BismuthMaterial>(hitInfo.material);
                float r = 1 - (1 - attenuation.x) * (1 - BismuthColor.x * bm->getChromaP());
                float g = 1 - (1 - attenuation.y) * (1 - BismuthColor.y * bm->getChromaP());
                float b = 1 - (1 - attenuation.z) * (1 - BismuthColor.z * bm->getChromaP());

                attenuation = Color(r, g, b);
            }
            return attenuation * RayColor(scattered, bouncesLeft - 1, rWorld);
        }
        return Color(0, 0, 0);


    }

    //Sky
    Vector3 unitDirection = Unit(rRay.GetDirection());
    double blue = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0.5, 0.7, 1.0);
}

Ray Camera::GetRay(int x, int y) const
{
    // Get a randomly sampled camera ray for the pixel at location i,j.

    Vector3 pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
    Vector3 pixelSample = pixelCenter + PixelSampleSquared();

    Position rayOrigin = center;
    Vector3 rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}


Vector3 Camera::PixelSampleSquared() const
{
    //Returns a random point in the square around a pixel at the origin
    double pX = -0.5 + RandomDouble();
    double pY = -0.5 + RandomDouble();
    return (pX * pixelDeltaX) + (pY * pixelDeltaY);
}


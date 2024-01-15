#include "HittableCollection.h"

using namespace std;

bool HittableCollection::Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const
{
    HitInfo tempInfo;
    bool hasHit = false;
    auto closestHit = rayTime.max;

    for (const shared_ptr<Hittable>& hittable : mPool) {
        if (hittable->Hit(rRay, Interval(rayTime.min, closestHit), tempInfo)) {
            hasHit = true;
            closestHit = tempInfo.time;
            hitInfo = tempInfo;
        }
    }

    return hasHit;
}


#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

class HittableCollection : public Hittable
{
private:
	std::vector<std::shared_ptr<Hittable>> mPool;
public:

	HittableCollection() = default;
	HittableCollection(std::shared_ptr<Hittable> hittable) { Add(hittable); }

	void Clear() { mPool.clear(); }
	void Add(std::shared_ptr<Hittable> hittable) { mPool.push_back(hittable); }

	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;
};

#ifndef BVH_H
#define BVH_H

#include "Hittable.hpp"
#include "HittableList.hpp"
#include "AABB.hpp"

#include <algorithm>

class Ray;
class HitRecord;

class BVHNode : public Hittable
{	
	public:
		BVHNode();
		BVHNode(const HittableList& list, double time0, double time1)
			: BVHNode(list.objects(), 0, list.objects().size(), time0, time1) {}
		BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1);

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

		virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

	public:
		std::shared_ptr<Hittable> _left;
		std::shared_ptr<Hittable> _right;
		AABB _box;
};

#endif
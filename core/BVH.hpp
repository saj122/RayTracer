#ifndef BVH_H
#define BVH_H

#include "Hittable.hpp"
#include "HittableList.hpp"
#include "AABB.hpp"

#include <algorithm>

class Ray;
class HitRecord;

inline bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
{
	AABB box_a;
	AABB box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
		std::cerr << "No bounding box in BVHNode constructor.\n";

	return box_a.aabb_min()[axis] < box_b.aabb_min()[axis];
}
inline bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) { return box_compare(a, b, 0); }
inline bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) { return box_compare(a, b, 1); }
inline bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) { return box_compare(a, b, 2); }

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
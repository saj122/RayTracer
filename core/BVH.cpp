#include "BVH.hpp"
#include "Utilities.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

#include <algorithm>

bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
{
	AABB box_a;
	AABB box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
		std::cerr << "No bounding box in BVHNode constructor.\n";

	return box_a.aabb_min()[axis] < box_b.aabb_min()[axis];
}

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1)
{
	auto objects = src_objects;

	int axis = random_int(0, 2);
	auto comparator = (axis == 0) ? box_x_compare
					: (axis == 1) ? box_y_compare
					: box_z_compare;

	size_t object_span = end - start;
	if (object_span == 1)
	{
		_left = _right = objects[start];
	}
	else if (object_span == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			_left = objects[start];
			_right = objects[start + 1];
		}
		else
		{
			_left = objects[start + 1];
			_right = objects[start];
		}
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		auto mid = start + object_span / 2;
		_left = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
		_right = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
	}

	AABB box_left, box_right;
	if (!_left->bounding_box(time0, time1, box_left)
		|| !_right->bounding_box(time0, time1, box_right))
		std::cerr << "No bounding box in BVHNode constructor.\n";

	_box = surrounding_box(box_left, box_right);
}

bool BVHNode::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	if (!_box.hit(r, t_min, t_max))
		return false;

	bool hit_left = _left->hit(r, t_min, t_max, rec);
	bool hit_right = _right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

	return hit_left || hit_right;
}

bool BVHNode::bounding_box(double time0, double time1, AABB& output_box) const
{
	output_box = _box;
	return true;
}
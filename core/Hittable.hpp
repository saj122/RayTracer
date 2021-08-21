#ifndef HITTABLE_H
#define HITTABLE_H

class HitRecord;
class Ray;
class AABB;

class Hittable
{
	public:
		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
		virtual bool bounding_box(double time0, double time1, AABB& output_box) const = 0;
};

#endif
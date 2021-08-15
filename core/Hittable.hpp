#ifndef HITTABLE_H
#define HITTABLE_H

class Ray;
class HitRecord;

class Hittable
{
	public:
		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif
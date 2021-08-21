#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.hpp"
#include "Vec3.hpp"
#include "Material.hpp"

#include <memory>

class HitRecord;
class Ray;

class Sphere : public Hittable
{
	public:
		Sphere() {}
		Sphere(Vec3 cen, double r, std::shared_ptr<Material> m) : _center(cen), _radius(r), _mat(m) {};

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

	public:
		Vec3 _center;
		double _radius;
		std::shared_ptr<Material> _mat;
};

#endif
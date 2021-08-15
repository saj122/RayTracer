#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.hpp"
#include "Vec3.hpp"

#include <memory>

class Material;

class Sphere : public Hittable
{
	public:
		Sphere() {}
		Sphere(Point3 cen, double r, std::shared_ptr<Material> m) : _center(cen), _radius(r), _mat(m) {};

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

	public:
		Point3 _center;
		double _radius;
		std::shared_ptr<Material> _mat;
};

#endif
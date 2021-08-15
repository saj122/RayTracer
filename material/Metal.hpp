#ifndef METAL_H
#define METAL_H

#include "Material.hpp"
#include "Vec3.hpp"

class Ray;
class HitRecord;

class Metal : public Material
{
	public:
		Metal(const Vec3& a, double f) : _albedo(a), _fuzz(f < 1.0 ? f : 1.0) {}
		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;
	private:
		Vec3 _albedo;
		double _fuzz;
};

#endif
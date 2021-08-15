#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.hpp"
#include "Vec3.hpp"

class Ray;
class HitRecord;

class Lambertian : public Material
{
	public:
		Lambertian(const Vec3& a) : _albedo(a) {}
		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;
	public:
		Vec3 _albedo;
};

#endif
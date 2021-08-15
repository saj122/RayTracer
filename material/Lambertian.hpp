#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.hpp"
#include "Vec3.hpp"

class Ray;
class HitRecord;

class Lambertian : public Material
{
	public:
		Lambertian(const Color& a) : _albedo(a) {}
		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
	public:
		Color _albedo;
};

#endif
#include "Isotropic.hpp"

#include "Texture.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include "HitRecord.hpp"

bool Isotropic::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
	scattered = Ray(rec.p, random_in_unit_sphere(), r_in.time());
	attenuation = _albedo->value(rec.u, rec.v, rec.p);
	return true;
}
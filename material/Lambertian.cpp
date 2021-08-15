#include "Lambertian.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = _albedo;
    return true;
}
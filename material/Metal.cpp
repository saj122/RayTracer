#include "Metal.hpp"

#include "Ray.hpp"
#include "HitRecord.hpp"

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
{
    Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + _fuzz * random_in_unit_sphere());
    attenuation = _albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
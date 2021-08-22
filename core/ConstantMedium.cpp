#include "ConstantMedium.hpp"

#include "Ray.hpp"
#include "Vec3.hpp"
#include "AABB.hpp"
#include "HitRecord.hpp"
#include "Utilities.hpp"

bool ConstantMedium::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    HitRecord rec1, rec2;

    if (!_boundary->hit(r, -infinity, infinity, rec1))
        return false;

    if (!_boundary->hit(r, rec1.t + 0.0001, infinity, rec2))
        return false;

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t = t_max;

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0)
        rec1.t = 0;

    const auto ray_length = r.direction().length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    const auto hit_distance = _neg_inv_density * log(random_double());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.at(rec.t);

    rec.normal = Vec3(1, 0, 0);  
    rec.front_face = true;     
    rec.mat = _phase_function;

    return true;
}

bool ConstantMedium::bounding_box(double time0, double time1, AABB& output_box) const
{
    return _boundary->bounding_box(time0, time1, output_box);
}
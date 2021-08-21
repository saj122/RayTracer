#include "Translate.hpp"

#include "Ray.hpp"
#include "HitRecord.hpp"
#include "AABB.hpp"

bool Translate::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    Ray moved_r(r.origin() - _offset, r.direction(), r.time());
    if(!_ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += _offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool Translate::bounding_box(double time0, double time1, AABB& output_box) const 
{
    if(!_ptr->bounding_box(time0, time1, output_box))
        return false;

    output_box = AABB(output_box.aabb_min() + _offset,
                      output_box.aabb_max() + _offset);
    return true;
}
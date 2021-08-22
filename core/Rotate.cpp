#include "Rotate.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"
#include "AABB.hpp"
#include "Utilities.hpp"

RotateY::RotateY(std::shared_ptr<Hittable> p, double angle) : _ptr(p) 
{
    auto radians = deg_to_rads(angle);
    _sin_theta = sin(radians);
    _cos_theta = cos(radians);
    _hasbox = _ptr->bounding_box(0, 1, _bbox);

    Vec3 min(infinity, infinity, infinity);
    Vec3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++) 
            {
                auto x = i * _bbox.aabb_max().x() + (1 - i) * _bbox.aabb_min().x();
                auto y = j * _bbox.aabb_max().y() + (1 - j) * _bbox.aabb_min().y();
                auto z = k * _bbox.aabb_max().z() + (1 - k) * _bbox.aabb_min().z();

                auto newx = _cos_theta * x + _sin_theta * z;
                auto newz = -_sin_theta * x + _cos_theta * z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) 
                {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    _bbox = AABB(min, max);
}

bool RotateY::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = _bbox;
    return _hasbox;
}


bool RotateY::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const 
{
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = _cos_theta * r.origin()[0] - _sin_theta * r.origin()[2];
    origin[2] = _sin_theta * r.origin()[0] + _cos_theta * r.origin()[2];

    direction[0] = _cos_theta * r.direction()[0] - _sin_theta * r.direction()[2];
    direction[2] = _sin_theta * r.direction()[0] + _cos_theta * r.direction()[2];

    Ray rotated_r(origin, direction, r.time());

    if (!_ptr->hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] = _cos_theta * rec.p[0] + _sin_theta * rec.p[2];
    p[2] = -_sin_theta * rec.p[0] + _cos_theta * rec.p[2];

    normal[0] = _cos_theta * rec.normal[0] + _sin_theta * rec.normal[2];
    normal[2] = -_sin_theta * rec.normal[0] + _cos_theta * rec.normal[2];

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}
#ifndef HITRECORD_H
#define HITRECORD_H

#include "math/Vec3.hpp"
#include "Material.hpp"

#include <memory>

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif
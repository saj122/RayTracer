#ifndef HITRECORD_H
#define HITRECORD_H

#include "Ray.hpp"
#include "Vec3.hpp"

class Material;

#include <memory>

class HitRecord
{
    public:
        Vec3 p;
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
#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "Vec3.hpp"
#include "Hittable.hpp"

#include <memory>

class HitRecord;
class Ray;
class AABB;

class Translate : public Hittable
{
    public:
        Translate(std::shared_ptr<Hittable> p, const Vec3& displacement) : _ptr(p), _offset(displacement) {}

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

    public:
        std::shared_ptr<Hittable> _ptr;
        Vec3 _offset;
};

#endif
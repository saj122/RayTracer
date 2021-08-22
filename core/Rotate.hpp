#ifndef ROTATE_H
#define ROTATE_H

#include "Hittable.hpp"
#include "AABB.hpp"

#include <memory>

class Ray;
class HitRecord;

class RotateY : public Hittable
{
    public:
        RotateY(std::shared_ptr<Hittable> p, double angle);

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Hittable> _ptr;
    double _sin_theta;
    double _cos_theta;
    bool _hasbox;
    AABB _bbox;
};

#endif
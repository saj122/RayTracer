#ifndef BOX_H
#define BOX_H

#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Vec3.hpp"

#include <memory>

class Material;
class Ray;
class HitRecord;

class Box : public Hittable {
public:
    Box() {}
    Box(const Vec3& p0, const Vec3& p1, std::shared_ptr<Material> ptr);

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    Vec3 _box_min;
    Vec3 _box_max;
    HittableList _sides;
};

#endif
#ifndef CONSTANTMEDIUM_H
#define CONSTANTMEDIUM_H

#include "Hittable.hpp"
#include "Isotropic.hpp"

#include <memory>

class Ray;
class HitRecord;
class AABB;
class Material;
class Texture;
class Vec3;

class ConstantMedium : public Hittable {
public:
    ConstantMedium(std::shared_ptr<Hittable> b, double d, std::shared_ptr<Texture> a)
        : _boundary(b),
        _neg_inv_density(-1 / d),
        _phase_function(std::make_shared<Isotropic>(a))
    {}

    ConstantMedium(std::shared_ptr<Hittable> b, double d, Vec3 c)
        : _boundary(b),
        _neg_inv_density(-1 / d),
        _phase_function(std::make_shared<Isotropic>(c))
    {}

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Hittable> _boundary;
    std::shared_ptr<Material> _phase_function;
    double _neg_inv_density;
};

#endif
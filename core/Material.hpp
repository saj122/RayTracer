#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec3.hpp"

class Ray;
class HitRecord;

class Material
{
    public:
        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
        virtual Vec3 emitted(double u, double v, const Vec3& p) const { return Vec3(0, 0, 0); }
};

#endif
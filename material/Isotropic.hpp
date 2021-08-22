#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "Material.hpp"
#include "SolidColor.hpp"

#include <memory>

class Texture;
class Ray;
class HitRecord;
class Vec3;

class Isotropic : public Material
{
    public:
        Isotropic(Vec3 c) : _albedo(std::make_shared<SolidColor>(c)) {}
        Isotropic(std::shared_ptr<Texture> a) : _albedo(a) {}

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;

    public:
        std::shared_ptr<Texture> _albedo;
};

#endif
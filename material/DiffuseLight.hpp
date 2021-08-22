#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "Material.hpp"
#include "SolidColor.hpp"

#include <memory>

class Ray;
class HitRecord;
class Texture;
class Vec3;

class DiffuseLight : public Material {
    public:
        DiffuseLight(std::shared_ptr<Texture> a) : _emit(a) {}
        DiffuseLight(Vec3 c) : _emit(std::make_shared<SolidColor>(c)) {}

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override { return false; }

        virtual Vec3 emitted(double u, double v, const Vec3& p) const override;
    public:
        std::shared_ptr<Texture> _emit;
};

#endif
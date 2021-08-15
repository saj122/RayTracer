#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.hpp"

class Ray;
class HitRecord;
class Vec3;

class Dielectric : public Material 
{
    public:
        Dielectric(double index_of_refraction) : _index_refraction(index_of_refraction) {}

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;

    public:
        double _index_refraction; 

    private:
        static double reflectance(double cosine, double ref_idx);
};

#endif
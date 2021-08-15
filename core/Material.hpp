#ifndef MATERIAL_H
#define MATERIAL_H

class Ray;
class HitRecord;
class Vec3;

class Material
{
    public:
        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

#endif
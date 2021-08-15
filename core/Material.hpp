#ifndef MATERIAL_H
#define MATERIAL_H

class Ray;
class HitRecord;
class Color;

class Material
{
    public:
        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

#endif
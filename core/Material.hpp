#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/Ray.hpp"
#include "math/Vec3.hpp"
#include "HitRecord.hpp"

#include <utility>

class Material
{
    public:
        virtual std::pair<bool, std::pair<Ray,Vec3>> scatter(const Ray& r_in, const HitRecord& rec);
};

#endif
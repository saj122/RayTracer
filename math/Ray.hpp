#ifndef RAY_H
#define RAY_H

#include "Vec3.hpp"

class Ray 
{
    public:
        Ray() : _orig{0.0,0.0,0.0}, _dir{0.0,0.0,0.0} {}
        Ray(const Vec3& origin, const Vec3& direction)
            : _orig(origin), _dir(direction), _tm(0.0) {}

        Ray(const Vec3& origin, const Vec3& direction, double time)
            : _orig(origin), _dir(direction), _tm(time) {}

        Vec3 origin() const  { return _orig; }
        Vec3 direction() const { return _dir; }
        double time() const    { return _tm; }

        Vec3 at(double t) const;
    private:
        Vec3 _orig;
        Vec3 _dir;
        double _tm;
};

#endif
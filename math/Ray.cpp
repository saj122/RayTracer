#include "Ray.hpp"

Vec3 Ray::at(double t) const
{
    return _orig + t*_dir;
}
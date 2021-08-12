#include "Ray.hpp"

Point3 Ray::at(double t) const
{
    return orig + t*dir;
}
#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"

class Camera
{
    public:
        Camera(
            Vec3 lookfrom,
            Vec3 lookat,
            Vec3   vup,
            double vfov, 
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double time0 = 0,
            double time1 = 0
        );

        Ray getRay(double s, double t) const;

    private:
        Vec3 _origin;
        Vec3 _lower_left_corner;
        Vec3 _horizontal;
        Vec3 _vertical;
        Vec3 _u, _v, _w;
        double _lens_radius;
        double _time0, _time1;
};

#endif
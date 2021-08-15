#include "Camera.hpp"

Camera::Camera(
            Vec3 lookfrom,
            Vec3 lookat,
            Vec3   vup,
            double vfov, 
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double time0,
            double time1
        )
{
    auto theta = deg_to_rads(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    _w = unit_vector(lookfrom - lookat);
    _u = unit_vector(cross(vup, _w));
    _v = cross(_w, _u);

    _origin = lookfrom;
    _horizontal = focus_dist * viewport_width * _u;
    _vertical = focus_dist * viewport_height * _v;
    _lower_left_corner = _origin - _horizontal/2 - _vertical/2 - focus_dist * _w;

    _lens_radius = aperture/2;
    _time0 = time0;
    _time1 = time1;
}

Ray Camera::getRay(double s, double t) const
{
    Vec3 rd = _lens_radius * random_in_unit_disk();
    Vec3 offset = _u * rd.x() + _v * rd.y();
    return Ray(
        _origin + offset,
        _lower_left_corner + s*_horizontal + t*_vertical - _origin - offset,
        random_double(_time0, _time1)
    );
}
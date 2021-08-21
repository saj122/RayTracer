#include "Sphere.hpp"

#include "Ray.hpp"
#include "HitRecord.hpp"
#include "AABB.hpp"

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    Vec3 oc = r.origin() - _center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - _radius*_radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) 
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - _center) / _radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = _mat;

    return true;
}

bool Sphere::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(_center - Vec3(_radius,_radius,_radius), _center + Vec3(_radius,_radius,_radius));
    return true;
}


// p: a given point on the sphere of radius one, centered at the origin.
// u: returned value [0,1] of angle around the Y axis from X=-1.
// v: returned value [0,1] of angle from Y=-1 to Y=+1.
//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>
void Sphere::get_sphere_uv(const Vec3& p, double& u, double& v)
{
    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2*pi);
    v = theta / pi;
}
#ifndef AARECT_H
#define AARECT_H

#include "Hittable.hpp"

#include <memory>

class Material;
class Ray;
class HitRecord;
class AABB;

class XYRect : public Hittable 
{
    public:
        XYRect() {}

        XYRect(
            double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<Material> mat
        ) : _x0(_x0), _x1(_x1), _y0(_y0), _y1(_y1), _k(_k), _mp(mat) {};

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

    public:
        std::shared_ptr<Material> _mp;
        double _x0, _x1, _y0, _y1, _k;
};

class XZRect : public Hittable 
{
public:
    XZRect() {}

    XZRect(
        double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat
    ) : _x0(_x0), _x1(_x1), _z0(_z0), _z1(_z1), _k(_k), _mp(mat) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> _mp;
    double _x0, _x1, _z0, _z1, _k;
};

class YZRect : public Hittable {
public:
    YZRect() {}

    YZRect(
        double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat
    ) : _y0(_y0), _y1(_y1), _z0(_z0), _z1(_z1), _k(_k), _mp(mat) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> _mp;
    double _y0, _y1, _z0, _z1, _k;
};

#endif
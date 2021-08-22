#include "Box.hpp"

#include "Material.hpp"
#include "AABB.hpp"
#include "HitRecord.hpp"
#include "AARect.hpp"

Box::Box(const Vec3& p0, const Vec3& p1, shared_ptr<Material> ptr) 
{
    _box_min = p0;
    _box_max = p1;

    _sides.add(std::make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    _sides.add(std::make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    _sides.add(std::make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    _sides.add(std::make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    _sides.add(std::make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    _sides.add(std::make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool Box::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const 
{
    return _sides.hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(double time0, double time1, AABB& output_box) const 
{
    output_box = AABB(_box_min, _box_max);
    return true;
}
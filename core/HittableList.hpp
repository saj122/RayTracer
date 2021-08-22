#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.hpp"

#include <memory>
#include <vector>

class Ray;
class HitRecord;
class AABB;

class HittableList : public Hittable 
{
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { _objects.clear(); }
        void add(std::shared_ptr<Hittable> object) { _objects.push_back(object); }

        std::vector<std::shared_ptr<Hittable>> objects() const
        {
            return _objects;
        }

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> _objects;
};

#endif
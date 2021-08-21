#ifndef ROTATE_H
#define ROTATE_H

#include "Hittable.hpp"

#include <memory>

class RotateY : public Hittable
{
    public:
        RotateY(std::shared_ptr<Hittable> p, double angle);

};

#endif
#include "Vec3.hpp"

Vec3 Vec3::operator-() const
{
    return Vec3(-v[0],-v[1],-v[2]);
}

double Vec3::operator[](int i) const
{
    return v[i];
}

double& Vec3::operator[](int i) 
{
    return v[i];
}

Vec3& Vec3::operator+=(const Vec3& e)
{
    v[0] += e.v[0];
    v[1] += e.v[1];
    v[2] += e.v[2];

    return *this;
}

Vec3& Vec3::operator*=(const double t)
{
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;

    return *this;
}

Vec3& Vec3::operator/=(const double t)
{
    return *this *= 1.0/t;
}

double Vec3::length() const 
{
    return sqrt(length_squared());
}

double Vec3::length_squared() const
{
    return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
}

bool Vec3::near_zero() const
{
    const auto s = 1e-8;
    return (fabs(v[0]) < s) && (fabs(v[1]) < s) && (fabs(v[2]) < s);
}
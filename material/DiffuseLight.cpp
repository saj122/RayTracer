#include "DiffuseLight.hpp"

#include "Vec3.hpp"
#include "Texture.hpp"

Vec3 DiffuseLight::emitted(double u, double v, const Vec3& p) const
{
	return _emit->value(u, v, p);
}
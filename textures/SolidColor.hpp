#ifndef SOLIDCOLOR_H
#define SOLIDCOLOR_H

#include "Texture.hpp"
#include "Vec3.hpp"

class SolidColor : public Texture
{
	public:
		SolidColor() {}
		SolidColor(Vec3 c) : _color(c) {}
		SolidColor(double r, double g, double b) : SolidColor(Vec3(r, g, b)) {}

		virtual Vec3 value(double u, double v, const Vec3& p) const override { return _color; }

	private:
		Vec3 _color;
};

#endif
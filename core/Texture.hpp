#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	public:
		virtual Vec3 value(double u, double v, const Vec3& p) const = 0;
};

#endif
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Hittable.hpp"
#include "Vec3.hpp"

#include <memory>

class HitRecord;
class Ray;
class Material;

class Triangle : public Hittable
{
	public:
		Triangle() {}
		Triangle(Vec3 a, Vec3 b, Vec3 c, std::shared_ptr<Material> m) : _point1(a), _point2(b), _point3(c), _mat(m) {};

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
		virtual bool bounding_box(double time0, double time1, AABB& output_box) const;

	private:
		static void get_triangle_uv(const Vec3& p, double& u, double& v);

	public:
		Vec3 _point1;
		Vec3 _point2;
		Vec3 _point3;
		Vec3 _u;
		Vec3 _v;
		Vec3 _w;
		std::shared_ptr<Material> _mat;
};

#endif
#ifndef AABB_H
#define AABB_H

#include "Vec3.hpp"
#include "Ray.hpp"

#include <algorithm>

class AABB
{
	public:
		AABB() {}
		AABB(const Vec3& a, const Vec3& b) { _min = a; _max = b; }

		Vec3 aabb_min() const { return _min; }
		Vec3 aabb_max() const { return _max; }

		bool hit(const Ray& r, double t_min, double t_max) const
		{
			for (int i = 0; i < 3; ++i) 
			{
				if (abs(r.direction()[i]) < 0.001)
				{
					if (r.origin()[i] < _min[i] || r.origin()[i] > _max[i]) return false;
				}
				else
				{
					double ood = 1.0 / r.direction()[i];
					double t1 = (_min[i] - r.origin()[i]) * ood;
					double t2 = (_max[i] - r.origin()[i]) * ood;

					if (t1 > t2) std::swap(t1, t2);
				
					t_min = fmax(t_min, t1);
					t_max = fmin(t_max, t2);

					if (t_min > t_max) return false;
				}
			}
			return true;
		}

		double area() const
		{
			auto a = _max.x() - _min.x();
			auto b = _max.y() - _min.y();
			auto c = _max.z() - _min.z();

			return 2 * (a * b + b * c + c * a);
		}

		int longest_axis() const
		{
			auto a = _max.x() - _min.x();
			auto b = _max.y() - _min.y();
			auto c = _max.z() - _min.z();
			if (a > b && a > c)
				return 0;
			else if (b > c)
				return 1;
			else
				return 2;
		}
	private:
		Vec3 _min;
		Vec3 _max;
};

inline AABB surrounding_box(AABB box0, AABB box1)
{
	Vec3 small(fmin(box0.aabb_min().x(), box1.aabb_min().x()),
		fmin(box0.aabb_min().y(), box1.aabb_min().y()),
		fmin(box0.aabb_min().z(), box1.aabb_min().z()));

	Vec3 big(fmax(box0.aabb_max().x(), box1.aabb_max().x()),
		fmax(box0.aabb_max().y(), box1.aabb_max().y()),
		fmax(box0.aabb_max().z(), box1.aabb_max().z()));

	return AABB(small, big);
}

#endif
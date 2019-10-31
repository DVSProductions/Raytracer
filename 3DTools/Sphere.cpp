#include "Sphere.h"
#include <iostream>
namespace DDD {
	direction Sphere::getNormal(point at)const noexcept {
		const auto top = at - this->p;
		return direction(top.x / radius, top.y / radius, top.z / radius);
	}
	Sphere::Sphere(std::string serialized) :renderable(point(0, 0, 0)) {
		this->load(serialized);
	}
	Sphere::Sphere(cgtools::point position, double radius, cgtools::Color color)noexcept :renderable(position) {
		this->radius = radius;
		rsq = radius * radius;
		c = color;
	}
	/// <summary>
	/// solves the equation. Using result pointers saves about 5% of render duration
	/// </summary>
	/// <returns></returns>
	constexpr uint8_t findPoint(double a, double b, double c, double* results1, double* results2) noexcept {
		const double c1 = b * b - 4 * a * c;
		if (c1 == 0) {
			*results1 = b == 0 ? 0 : (-b) / (2 * a);
			return 1;
		}
		else if (c1 < 0)
			return 0;
		else {
			const double sqr = sqrt(c1);
			const double mb = -b;
			const double a2 = 2 * a;
			*results1 = (mb + sqr) / a2;
			*results2 = (mb - sqr) / a2;
			return 2;
		}
	}


	Hit DDD::Sphere::intersect(Ray r) const {
		const auto x0 = r.x0 - p;
		const double a = r.dir[r.dir];
		const double b = 2 * x0[r.dir];
		const double c = x0[x0] - rsq;
		double results1 = 0, results2 = 0;
		double t = 0;
		const auto solutions = findPoint(a, b, c, &results1, &results2);//Pointers save 5% vs passing array
		if (solutions == 0)return Hit(false);
		else if (solutions == 1)t = results1;
		else t = results1 < results2 ? results1>r.tmin ? results1 : results1 : results2;
		if (t < r.tmin || t > r.tmax)return Hit(false);
		const auto intersection = point(t * r.dir);
		return Hit(t, intersection, getNormal(intersection), this->c);
	}

	std::string Sphere::serialize() const {
		return renderable::includeClassID(std::to_string(radius) + "&" + c.serialize() + "&" + p.serialize(), DDD_CLASS_SPHERE);
	}

	void Sphere::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "&");
		f_chars(ret[0], radius);
		c.load(ret[1]);
		p.load(ret[2]);
	}

}
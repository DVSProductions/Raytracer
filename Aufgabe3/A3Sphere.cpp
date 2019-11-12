#include "A3Sphere.h"
#include <iostream>
using std::cout; using std::endl;

cgtools::direction A3Sphere::getNormal(cgtools::point at)const noexcept {
	const auto top = at - this->p;
	return cgtools::direction(top.x / radius, top.y / radius, top.z / radius);
}

A3Sphere::A3Sphere(cgtools::point position, double radius, cgtools::Color color)noexcept :renderable(position) {
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
	else if (c1 < 0)return 0;
	else {
		const double sqr = sqrt(c1);
		const double mb = -b;
		const double a2 = 2 * a;
		*results1 = (mb + sqr) / a2;
		*results2 = (mb - sqr) / a2;
		return 2;
	}
}


DDD::Hit A3Sphere::intersect(DDD::Ray r) const {
	const auto x0 = r.x0 - p;
	const double a = r.dir[r.dir];
	const double b = 2 * x0[r.dir];
	const double c = x0[x0] - rsq;
	double results1 = 0, results2 = 0;
	double t = 0;
	const auto solutions = findPoint(a, b, c, &results1, &results2);//Pointers save 5% vs passing array
	if (solutions == 0)return DDD::Hit();
	else if (solutions == 1)t = results1;
	else t = results1 < results2 ? results1>r.tmin ? results1 : results1 : results2;
	if (t < r.tmin || t > r.tmax)return DDD::Hit();
	const auto intersection = cgtools::point(t * r.dir);
	return DDD::Hit(t, intersection, getNormal(intersection), this->c);
}

std::string A3Sphere::serialize() const {
	return  std::to_string(radius) + "&" + c.serialize() + "&" + p.serialize();
}

void A3Sphere::load(std::string serialized) {
	auto ret = Serializable::split(serialized, "&");
	f_chars(ret[0], radius);
	c.load(ret[1]);
	p.load(ret[2]);
}

size_t A3Sphere::size() const {
	return sizeof(A3Sphere);
}
DDD::renderable* A3Sphere::clone() const {
	return new A3Sphere(p, radius, c);
}

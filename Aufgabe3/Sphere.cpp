#include "Sphere.h"
#include <iostream>
using std::cout; using std::endl;

direction Sphere::getNormal(point at) {
	auto top = at - this->p;
	return direction(top.x / radius, top.y / radius, top.z / radius);
}

Sphere::Sphere(cgtools::point position, double radius, cgtools::Color color) :renderable(position) {
	this->radius = radius;
	rsq = radius * radius;
	c = color;
}
uint8_t findPoint(double a, double b, double c, double results[2]) {
	double c1 = b * b - 4 * a * c;
	if (c1 == 0) {
		results[0] = b == 0 ? 0 : (-b) / (2 * a);
		return 1;
	}
	else if (c1 < 0)return 0;
	else {
		double sqr = sqrt(c1);
		results[0] = ((-b) + sqr) / (2 * a);
		results[1] = ((-b) - sqr) / (2 * a);
		return 2;
	}
}

Hit* Sphere::intersect(Ray r) {
	auto x0 = r.x0 - p;
	double results[2] = { 0 };
	double a = r.dir[r.dir];
	double b = 2 * (x0[r.dir]);
	double c = x0[x0] - rsq;
	double t = 0;
	int solutions = findPoint(a, b, c, results);
	if (solutions == 0)return nullptr;
	else if (solutions == 1)t = results[0];
	else t = results[0] < results[1] ? results[0]>r.tmin ? results[0] : results[0] : results[1];
	if (t < r.tmin||t > r.tmax)return nullptr;
	direction d = t * r.dir;
	point intersection = point(d.x, d.y, d.z);
	return new Hit(t, intersection, getNormal(intersection), this->c);
}

#pragma once
#include <renderable.h>
#include "Hit.h"
#include "Ray.h"
using namespace DDD;
class Sphere :
	public renderable {
	double radius;
	double rsq;
	cgtools::Color c;
	direction getNormal(point at);
public:
	Sphere(cgtools::point position, double radius, cgtools::Color color);
	Hit *intersect(Ray r);
};

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
public:
	direction getNormal(point at) const noexcept;
	Sphere(cgtools::point position, double radius, cgtools::Color color) noexcept;
	Hit* intersect(Ray r)const override;
};

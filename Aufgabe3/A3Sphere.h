#pragma once
#include <renderable.h>
#include "Hit.h"
#include "Ray.h"
class A3Sphere :
	public DDD::renderable {
	double radius;
	double rsq;
	cgtools::Color c;
public:
	direction getNormal(point at) const noexcept;
	A3Sphere(cgtools::point position, double radius, cgtools::Color color) noexcept;
	DDD::Hit intersect(DDD::Ray r)const override;
	std::string serialize()const override;
	void load(std::string serialized) override;
};

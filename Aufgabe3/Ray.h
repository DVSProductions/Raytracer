#pragma once
#include "direction.h"
#include "point.h"
using namespace cgtools;
class Ray {
	point xZero;
	direction dir;
	double tmin;
	double tmax;
public:
	point pointAt(double t) noexcept;
};


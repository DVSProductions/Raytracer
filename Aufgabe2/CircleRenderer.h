#pragma once
#include "ColorFunc.h"
#include <vector>
#include "Circle.h"
class CircleRenderer :public ColorFunc {
	std::vector<Circle> circles;
public:
	CircleRenderer(int width, int height);
	Color getColor(double x, double y);
};


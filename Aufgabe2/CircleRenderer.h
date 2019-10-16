#pragma once
#include "Renderer.h"
#include <vector>
#include "Circle.h"
class CircleRenderer :public Renderer {
	std::vector<Circle> circles;
public:
	CircleRenderer(int width, int height);
	Color getColor(double x, double y);
};


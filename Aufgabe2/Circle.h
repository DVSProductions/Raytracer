#pragma once
#include "Color.h"
class Circle
{
	double x;
	double y;
public:
	Color color;
	double radius;
	Circle(double x, double y, double radius, Color c);
	//Detects if Point is within circle
	bool isPointInCircle(double x, double y);
};


#pragma once
#include "Color.h"
class Circle
{
	double x;
	double y;
	double boundXP, boundXN;
	double boundYP, boundYN;
	double innerYP, innerYN;
	double innerXP, innerXN;
public:
	Color color;
	double radius;
	Circle(double x, double y, double radius, Color c);
	//Detects if Point is within circle
	bool isPointInCircle(double x, double y);
};


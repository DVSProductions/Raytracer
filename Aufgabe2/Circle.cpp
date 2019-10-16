#include "Circle.h"
#include <iostream>
using namespace std;

Circle::Circle(double x, double y, double radius, Color c) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->color = Color(c);
	boundXP = x + radius;
	boundXN = x - radius;
	boundYP = y + radius;
	boundYN = y - radius;
}

/// <summary>
/// Detects if Point is within circle
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
bool Circle::isPointInCircle(double x, double y) {
	//Avoid costly math if out of bounds
	if (x > boundXP || x<boundXN || y > boundYP || y < boundYN)return false;
	double modx = this->x - x;
	double mody = this->y - y;
	return radius >= sqrt(modx * modx + mody * mody);
}

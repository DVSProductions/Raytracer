#include "Circle.h"
#include <iostream>
using namespace std;

Circle::Circle(double x, double y, double radius, Color c){
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->color = Color(c);
}

/// <summary>
/// Detects if Point is within circle
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
bool Circle::isPointInCircle(double x, double y){
	double modx = this->x - x;
	double mody = this->y - y;
	return radius >= sqrt(abs(modx * modx + mody * mody));
}

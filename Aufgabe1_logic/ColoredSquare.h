#pragma once
#include "ColorFunc.h"
class ColoredSquare :
	public ColorFunc {
	double left,right,top,bottom;
	Color color;
public:
	ColoredSquare(Color color, int a, int screenX, int screenY);
	Color getColor(double x, double y);

};


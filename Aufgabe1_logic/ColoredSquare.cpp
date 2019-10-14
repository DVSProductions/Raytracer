#include "ColoredSquare.h"
#include "A1Defines.h"
ColoredSquare::ColoredSquare(Color color, int a, int screenX, int screenY) {
	a *= scaling;
	screenX /= 2;
	screenY /= 2;
	a /= 2;
	left = screenX - a;
	right = screenX + a;
	top = screenY - a;
	bottom = screenY + a;
	this->color = color;
}

Color ColoredSquare::getColor(double x, double y) {
	return x > left&& x<right && y>top&& y < bottom ? color : black;
}

#include "ConstantColor.h"
#include "DLLInfo.h"
#define _USE_MATH_DEFINES
#include <math.h>
ConstantColor::ConstantColor(Color* color) {
	this->color = Color(color);
}

ConstantColor::ConstantColor(const Color* color) {
	this->color = Color(color);
}

ConstantColor::~ConstantColor() {}

Color ConstantColor::getColor(double x, double y) {
	//return &color;
	//return Color((sin(x * M_PI / 180.0) + 1) / 2.0, (cos(y * M_PI / 180.0) + 1) / 2, (sin(y * M_PI / 180.0) + 1)/2);
	// new Color((cos(y * M_PI / 180.0) + 1) / 4 + (cos(x * M_PI / 180.0) + 1) / 4, (tan((x - M_PI / 2)) + 1) / 4 + (tan((y/10 - M_PI / 2)) + 1) / 4, (sin(y / 10 * M_PI / 180.0) + 1) / 4 + (sin(x * M_PI / 180.0) + 1) / 4);
	return Color(0, (tan((x * M_PI) / (160 * scaling) - M_PI / 2) + 1) / 4 + (tan((y * M_PI) / (90 * scaling) - M_PI / 2) + 1) / 4, 0);
}

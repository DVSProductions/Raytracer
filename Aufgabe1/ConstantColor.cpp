#include "ConstantColor.h"
#include "DLLInfo.h"
#define _USE_MATH_DEFINES
#include <math.h>

ConstantColor::ConstantColor(Color* color) noexcept {
	this->color = Color(color);
}

ConstantColor::ConstantColor(const Color* color)noexcept {
	this->color = Color(color);
}

Color ConstantColor::getColor(double x, double y)noexcept {
	//return &color;
	//return Color((sin(x * M_PI / 180.0) + 1) / 2.0, (cos(y * M_PI / 180.0) + 1) / 2, (sin(y * M_PI / 180.0) + 1)/2);
	// new Color((cos(y * M_PI / 180.0) + 1) / 4 + (cos(x * M_PI / 180.0) + 1) / 4, (tan((x - p05)) + 1) / 4 + (tan((y/10 - p05)) + 1) / 4, (sin(y / 10 * M_PI / 180.0) + 1) / 4 + (sin(x * M_PI / 180.0) + 1) / 4);
	return Color(0, (tan(M_PI * (x / width - 0.5)) + 1) / 4 + (tan(M_PI * (y / height - 0.5)) + 1) / 4, 0);//factorized for extra performance
}

std::shared_ptr<Renderer> ConstantColor::clone() {
	return nullptr;
}

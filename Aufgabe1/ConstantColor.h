#pragma once
#include "ColorFunc.h"
class ConstantColor : public ColorFunc {
	Color color;
public:
	ConstantColor(const Color* color);
	ConstantColor(Color* color);
	~ConstantColor();
	Color getColor(double x, double y);
};


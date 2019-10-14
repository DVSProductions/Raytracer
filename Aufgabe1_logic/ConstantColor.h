#pragma once
#include "ColorFunc.h"
class ConstantColor : public ColorFunc {
	Color color;
public:
	ConstantColor(Color color);
	~ConstantColor();
	Color getColor(double x, double y);
};


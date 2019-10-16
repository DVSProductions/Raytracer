#pragma once
#include "Renderer.h"
class ConstantColor : public Renderer {
	Color color;
public:
	ConstantColor(const Color* color);
	ConstantColor(Color* color);
	~ConstantColor();
	Color getColor(double x, double y);
};


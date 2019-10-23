#pragma once
#include "Renderer.h"
class ConstantColor : public Renderer {
	Color color;
public:
	ConstantColor(const Color* color)noexcept;
	ConstantColor(Color* color)noexcept;
	Color getColor(double x, double y)noexcept override;
};


#pragma once
#include "Renderer.h"
using namespace cgtools;
class ConstantColor : public Renderer {
	Color color;
public:
	ConstantColor(const Color* color)noexcept;
	ConstantColor(Color* color)noexcept;
	Color getColor(double x, double y)noexcept override;
	std::shared_ptr<Renderer> clone()override;
};


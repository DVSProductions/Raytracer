#pragma once
#include "Renderer.h"
class ColoredSquare : public Renderer {
	double left, right, top, bottom;
	Color color;
public:
	ColoredSquare(const Color* color, int a, int screenX, int screenY);
	Color getColor(int x, int y);
	inline Color getColor(double x, double y) { return getColor((int)x, (int)y); }
};


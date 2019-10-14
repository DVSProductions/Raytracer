#pragma once
#include "ColorFunc.h"
#include "ColoredSquare.h"
class Checkered :	public ColorFunc {
	Color A, B;
	int mod;
	ColoredSquare child;
public:
	Checkered(Color bgA, Color bgB, Color rect, int bgMOD, int rectA, int screenX, int screenY);
	Color getColor(int x, int y);
	inline Color getColor(double x, double y) { return getColor((int)x, (int)y); }
};


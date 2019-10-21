#pragma once
#include "Renderer.h"
#include "ColoredSquare.h"
class Checkered : public Renderer {
	Color A, B;
	int mod;
	ColoredSquare child;
public:
	Checkered(const Color* bgA, const Color* bgB, const Color* rect, int bgMOD, int rectA, int screenX, int screenY);
	Color getColor(double x, double y);
};


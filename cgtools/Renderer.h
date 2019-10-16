#pragma once
#include "Color.h"
class Renderer {
public:
	virtual Color getColor(double x, double y) = 0;
};


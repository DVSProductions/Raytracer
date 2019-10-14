#pragma once
#include "Color.h"
class ColorFunc {
public:
	virtual Color getColor(double x, double y) = 0;
};


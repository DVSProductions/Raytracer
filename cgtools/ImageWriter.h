#pragma once
#include "cgtools.h"
#include <string>
#include <cmath>
static class ImageWriter {
	static double clamp(double v) {
		return fmin(fmax(0, v), 1);
	}
public:
	static unsigned int write(std::string filename, double * data, int width, int height, bool linear=true);
};
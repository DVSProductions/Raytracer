#pragma once
#include <string>
#include "Color.h"
class Image {
	double gamma;
	double * buffer;
	size_t sizeX, sizeY;
public:
	Image(size_t width, size_t height, double gamma=1.0);
	void setPixel(size_t x, size_t y, Color color);
	unsigned int write(std::string filename);
	~Image();
};


#include "Image.h"
#include "ImageWriter.h"
#include <iostream>
using namespace std;
Image::Image(size_t width, size_t height) {
	sizeX = width;
	sizeY = height;
	buffer = new double[height*width * 3ul];
}

void Image::setPixel(size_t x, size_t y, Color color) {
	size_t idx = (y * sizeX + x) * 3ul;
	buffer[idx++] = color.r;
	buffer[idx++] = color.g;
	buffer[idx] = color.b;
}

unsigned int Image::write(std::string filename) {
	return ImageWriter::write(filename, buffer, sizeX, sizeY);
}

Image::~Image() {
	delete[] buffer;
}

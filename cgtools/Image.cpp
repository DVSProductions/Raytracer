#include "Image.h"
#include "ImageWriter.h"
using namespace cgtools;
using std::make_unique;
Image::Image(size_t width, size_t height, double gamma) {
	this->gamma = 1.0 / gamma;
	sizeX = width;
	sizeY = height;
	buffer = make_unique< double[]>(height * width * 3ul);
}

void Image::setPixel(size_t x, size_t y, Color color) noexcept {
	if (x >= sizeX || y >= sizeY)return;
	const size_t idx = (y * sizeX + x) * 3ul;
	buffer[idx] = pow(color.r, this->gamma);
	buffer[idx + 1] = pow(color.g, this->gamma);
	buffer[idx + 2] = pow(color.b, this->gamma);
}

unsigned int Image::write(std::string filename) {
	return ImageWriter::write(filename, buffer, sizeX, sizeY);
}
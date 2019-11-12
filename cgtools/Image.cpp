#include "Image.h"
#include "ImageWriter.h"
#include <Windows.h>
using namespace cgtools;
using std::make_unique;
Image::Image(size_t width, size_t height, double gamma) {
	this->gamma = 1.0 / gamma;
	sizeX = width;
	sizeY = height;
	buffer = make_unique< uint8_t[]>(height * width * 4ul);
}
uint8_t quanizise(double v, double gamma) {
	return static_cast<uint8_t>( fmin(fmax(0, pow(v, gamma)), 1) * UINT8_MAX);
}
void Image::setPixel(size_t x, size_t y, Color color) noexcept {
	if (x >= sizeX || y >= sizeY)return;
	const size_t idx = (y * sizeX + x) * 4ul;
	buffer[idx + 0] = quanizise(color.r, this->gamma);
	buffer[idx + 1] = quanizise(color.g, this->gamma);
	buffer[idx + 2] = quanizise(color.b, this->gamma);
	buffer[idx + 3] = 255;
	//OutputDebugStringA((color.toString() + "\n").c_str());
	//OutputDebugStringA((std::to_string(buffer[idx + 0])+", "+std::to_string(buffer[idx + 1])+", "+std::to_string(buffer[idx + 2])+"\n").c_str());
}

unsigned int Image::write(std::string filename) {
	return ImageWriter::write(filename, buffer, sizeX, sizeY);
}
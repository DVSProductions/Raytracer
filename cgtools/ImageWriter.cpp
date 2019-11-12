#include "ImageWriter.h"
#include "lodepng.h"
#include <exception>
#include <memory>
using namespace cgtools;
unsigned int ImageWriter::write(std::string filename, const std::unique_ptr<uint8_t[]>& data, size_t width, size_t height, bool linear) {
	//std::vector<uint8_t> parsed;
	//parsed.reserve(4ul * width * height);
	for (size_t y = 0; y != height; y++) {
		for (size_t x = 0; x != width; x++) {
			const size_t i = (width * y + x) * 4;
			//OutputDebugStringA((std::to_string(data[i + 0])+", "+std::to_string(data[i + 1])+", "+std::to_string(data[i + 2])+"\n").c_str());
			//parsed.push_back(255);
		}
	}
	remove(filename.c_str());
	return lodepng::encode(filename, data.get(), static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

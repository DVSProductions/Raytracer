#include "ImageWriter.h"
#include "lodepng.h"
#include <exception>
#include <memory>



unsigned int ImageWriter::write(std::string filename, const std::unique_ptr<double[]> &data, size_t width, size_t height, bool linear) {
	std::vector<uint8_t> parsed;
	parsed.reserve(4ul * width * height);
	for (size_t y = 0; y != height; y++) {
		for (size_t x = 0; x != width; x++) {
			const size_t i = (width * y + x) * 3;
			parsed.push_back((uint8_t)(clamp(data[i + 0]) * UINT8_MAX));
			parsed.push_back((uint8_t)(clamp(data[i + 1]) * UINT8_MAX));
			parsed.push_back((uint8_t)(clamp(data[i + 2]) * UINT8_MAX));
			parsed.push_back(255);
		}
	}
	remove(filename.c_str());
	return lodepng::encode(filename, parsed, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

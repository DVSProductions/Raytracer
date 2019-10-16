#include "ImageWriter.h"
#include "lodepng.h"
#include <exception>


unsigned int ImageWriter::write(std::string filename, double* data, int width, int height, bool linear) {
	std::vector<uint8_t> parsed;
	parsed.reserve(4ul * width * height);
	for (int y = 0; y != height; y++) {
		for (int x = 0; x != width; x++) {
			int i = (width * y + x) * 3;
			parsed.push_back((uint8_t)(clamp(data[i + 0]) * UINT8_MAX));
			parsed.push_back((uint8_t)(clamp(data[i + 1]) * UINT8_MAX));
			parsed.push_back((uint8_t)(clamp(data[i + 2]) * UINT8_MAX));
			parsed.push_back(255);
		}
	}
	remove(filename.c_str());
	return lodepng::encode(filename, parsed, width, height);
}

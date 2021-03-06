#include "Image.h"
#include "ImageWriter.h"
//#include <Windows.h>
#include <fstream>
namespace cgtools {
	using std::make_unique;
	Image::Image(size_t width, size_t height, double gamma) {
		this->gamma = 1.0 / gamma;
		sizeX = width;
		sizeY = height;
		buffer = make_unique< uint8_t[]>(height * width * 4ul);
	}
	uint8_t quanizise(double v, double gamma)noexcept {
		return static_cast<uint8_t>(fmin(fmax(0, pow(v, gamma)), 1) * UINT8_MAX);
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
		return ImageWriter::write(filename, buffer.get(), sizeX, sizeY);
	}

	void cgtools::Image::dump(std::string dumpName) {
		std::ofstream of(dumpName, std::ios::binary | std::ios::out | std::ios::trunc);
		const size_t max = sizeX * sizeY * 4;
		for (size_t n = 0; n != max; n += 4) {
			if (buffer[n + 3] == 0)break;
			of << buffer[n + 0] << buffer[n + 1] << buffer[n + 2];
		}
		of.close();
	}

	size_t cgtools::Image::loadFromDump(std::string dumpName) {
		std::ifstream in(dumpName, std::ios::binary | std::ios::in);
		const size_t max = sizeX * sizeY * 4;
		size_t n = 0;
		for (; n != max && !in.eof(); n += 4) {
			in >> buffer[n + 0];
			in >> buffer[n + 1];
			in >> buffer[n + 2];
		}
		in.close();
		return n;
	}
	size_t Image::getX() const noexcept {
		return sizeX;
	}
	size_t Image::getY() const noexcept {
		return sizeY;
	}
	void Image::blastGameImage(void* data) {
		if (data == NULL)return;
		const size_t max = sizeX * sizeY * 4ul;
		const auto src = buffer.get();
		uint8_t* ret = (uint8_t*)data;
		for (size_t source = 0, target = 0; source < max; source++) {
			if ((source + 1) % 4 != 0)
				ret[target++] = src[source];
		}
	}
	void Image::blastGameImage(uint8_t** data) {
		*data = buffer.get();
	}
}
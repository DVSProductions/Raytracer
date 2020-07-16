#include "ImageTexture.h"
namespace cgtools {
	cgtools::ImageTexture::ImageTexture(std::string filename) {

	}

	Color cgtools::ImageTexture::getColor(double x, double y) {
		return Color();
	}

	std::shared_ptr<Renderer> cgtools::ImageTexture::clone() {
		return std::shared_ptr<Renderer>();
	}
}
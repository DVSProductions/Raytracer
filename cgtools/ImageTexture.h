#pragma once
#include <string>
#include "Color.h"
#include "Renderer.h"
namespace cgtools {
	class ImageTexture : public Renderer {
	public:
		ImageTexture(std::string filename);
		Color getColor(double x, double y);
		std::shared_ptr<Renderer> clone();
	};

}
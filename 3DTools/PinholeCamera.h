#pragma once
#include <ACamera.h>
#include "Background.h"
namespace DDD {
	class PinholeCamera :public ACamera {
		double w0_5, h0_5;
		double a05tan;
		double zpre;
		Background background;
		friend class ACamera;
		PinholeCamera(std::string serialized);
	public:
		const static int CLASSID = 0;
		PinholeCamera(double angle, const cgtools::point& position, Background background) noexcept;
		PinholeCamera(double angle, const cgtools::point& position, Background background, unsigned short reflectionDepth) noexcept;
		void init() noexcept;
		void precalculation(double angle) noexcept;
		DDD::Ray generateRay(double x, double y) noexcept;
		cgtools::Color getColor(double x, double y) override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const override;
	};
}

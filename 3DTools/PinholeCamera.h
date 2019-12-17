#pragma once
#include "ACamera.h"
#include "Background.h"
#include "../cgtools/Color.h"
namespace DDD {
	class PinholeCamera :public ACamera{
		friend class ACamera;
		const static int CLASSID = 0;
		PinholeCamera(std::string serialized);
	protected:
		double w0_5, h0_5;
		double a05tan;
		double zpre;
		Background background;
		std::unique_ptr<cgtools::Color[]> eStack;
		std::unique_ptr<cgtools::Color[]> aStack;
		PinholeCamera();
	public:
		PinholeCamera(double angle, Background background) noexcept;
		PinholeCamera(double angle, Background background, unsigned short reflectionDepth) noexcept;
		void init() noexcept override;
		DDD::Ray generateRay(double x, double y) noexcept;
		cgtools::Color getColor(double x, double y) override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const override;
		std::shared_ptr<cgtools::Renderer> clone()override;
	};
}

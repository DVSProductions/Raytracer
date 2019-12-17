#pragma once
#include "PinholeCamera.h"
#include "../cgtools/Matrix.h"
#include "../cgtools/transformStack.h"
namespace DDD {
	class PinholeCamera;
	class MovablePinholeCamera:public PinholeCamera {
		cgtools::transformStack ts;
		cgtools::matrix transformation;
		cgtools::point newCenter=cgtools::point(0,0,0);
		MovablePinholeCamera(std::string serialized);
		friend class ACamera;
		const static int CLASSID = 1;
	public:
		MovablePinholeCamera(double angle, Background background) noexcept;
		MovablePinholeCamera(double angle, Background background, unsigned short reflectionDepth) noexcept;
		MovablePinholeCamera(double angle, Background background, unsigned short reflectionDepth, cgtools::transformStack stack) noexcept;
		void init() noexcept;
		Ray generateRay(double x, double y) noexcept;
		cgtools::Color getColor(double x, double y) override;
		std::string serialize() const override;
		void load(std::string serialized)override;
		size_t size() const override;
		std::shared_ptr<cgtools::Renderer> clone()override;
	};
}
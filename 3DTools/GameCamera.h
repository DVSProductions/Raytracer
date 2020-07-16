#pragma once
#include "MovablePinholeCamera.h"
namespace DDD {
	class GameCamera :public MovablePinholeCamera {
		const static int CLASSID = 2;
		cgtools::matrix rotationMatrix;
		double previousY = 0;
	public:
		GameCamera(double angle, Background background, unsigned short reflectionDepth) noexcept;
		std::shared_ptr<cgtools::Renderer> clone()override;
		void moveCamera(double x, double y, double z) noexcept;
		void rotateCamera(double x, double y, double z)noexcept;
		void reload(double angle, unsigned short reflections, std::string bg);
	};
}

#include "GameCamera.h"
#include "../cgtools/Matrix.h"
namespace DDD {
	GameCamera::GameCamera(double angle, Background background, unsigned short reflectionDepth) noexcept :MovablePinholeCamera(angle, background, reflectionDepth)
	{
	}
	std::shared_ptr<cgtools::Renderer> GameCamera::clone() {
		auto ret = std::make_shared<GameCamera>(angle, background, reflectionDepth);
		ret->setScene(this->scene);
		ret->transformation = transformation * rotationMatrix;
		ret->init();
		return ret;
	}
	void GameCamera::moveCamera(double x, double y, double z) noexcept {
		transformation *= cgtools::matrix::createTranslation(x, y, z);
	}
	void GameCamera::rotateCamera(double x, double y, double z) noexcept {
		rotationMatrix = cgtools::matrix();
		if (x != 0)
			rotationMatrix *= cgtools::matrix::createRotationX(x);
		if (y != previousY) {
			transformation *= cgtools::matrix::createRotationY(y - previousY);
			previousY = y;
		}
		if (z != 0.0)
			rotationMatrix *= cgtools::matrix::createRotationZ(z);
	}
	void GameCamera::reload(double angle, unsigned short reflections, std::string bg) {
		this->angle = angle;
		this->reflectionDepth = reflections;
		background.load(bg);
	}
}
#pragma once
#include <point.h>
#include <Renderer.h>
#include "Ray.h"
#include "Scene.h"
#include <memory>
using namespace cgtools;
class Camera :public  Renderer {
protected:
	std::shared_ptr<DDD::Scene> scene;
	point position;
	double angle;
	Camera(const point& pos, const double& angle) noexcept;
public:
	void setScene(std::shared_ptr<DDD::Scene> s)noexcept;
	void move(const point& newPos) noexcept;
	void setAngle(const double& newAngle) noexcept;
	//void setScene(std::shared_ptr<DDD::Scene>& s);
};


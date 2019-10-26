#pragma once
#include <point.h>
#include <Renderer.h>
#include "Ray.h"
#include "Scene.h"
using namespace cgtools;
class Camera :public  Renderer {
protected:
	DDD::Scene * scene=nullptr;
	point position;
	double angle;
	Camera(const point& pos, const double& angle);
public:
	void setScene(DDD::Scene* s);
};


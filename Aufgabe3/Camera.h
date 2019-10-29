#pragma once
#include <point.h>
#include <Renderer.h>
#include "Ray.h"
#include "Scene.h"
#include "ISerializable.h"
#include <memory>
using namespace cgtools;
class Camera :public  Renderer,public ISerializable{
protected:
	std::shared_ptr<DDD::Scene> scene;
	point position;
	double angle;
	Camera(const point& pos, const double& angle) noexcept;
public:
	void setScene(std::shared_ptr<DDD::Scene> s)noexcept;
	void move(const point& newPos) noexcept;
	void setAngle(const double& newAngle) noexcept;

	// Geerbt über ISerializable
	std::string serialize() const override;
	void load(std::string serialized)override;
	//void setScene(std::shared_ptr<DDD::Scene>& s);
};


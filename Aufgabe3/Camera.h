#pragma once
#include <point.h>
#include "Color.h"
#include <Renderer.h>
#include "Ray.h"
#include "Scene.h"
#include "ISerializable.h"
#include <memory>
class Camera :public  cgtools::Renderer, public ISerializable {
protected:
	std::shared_ptr<DDD::Scene> scene;
	cgtools::point position;
	double angle;
	Camera(const cgtools::point& pos, const double& angle) noexcept;
public:
	void setScene(std::shared_ptr<DDD::Scene> s)noexcept;
	void move(const cgtools::point& newPos) noexcept;
	void setAngle(const double& newAngle) noexcept;

	// Geerbt über ISerializable
	std::string serialize() const override;
	void load(std::string serialized)override;
	size_t size() const override;
	//void setScene(std::shared_ptr<DDD::Scene>& s);
};


#pragma once
#include <point.h>
#include <Renderer.h>
#include "Ray.h"
#include "Scene.h"
#include "ISerializable.h"
#include <memory>
namespace DDD {
	class ACamera :public cgtools::Renderer, public ISerializable {
	protected:
		std::shared_ptr<DDD::Scene> scene;
		cgtools::point position;
		double angle;
		ACamera(const cgtools::point& pos, const double& angle) noexcept;
		static std::string includeClassID(std::string data, int CID);
	public:
		void setScene(std::shared_ptr<DDD::Scene> s)noexcept;
		void move(const cgtools::point& newPos) noexcept;
		void setAngle(const double& newAngle) noexcept;

		// Geerbt über ISerializable
		std::string serialize() const override;
		void load(std::string serialized)override;
		//void setScene(std::shared_ptr<DDD::Scene>& s);
	};
}


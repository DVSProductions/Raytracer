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
		unsigned short reflectionDepth = 1;
		std::shared_ptr<DDD::Scene> scene;
		cgtools::point position;
		double angle;
		ACamera(const cgtools::point& pos, const double& angle) noexcept;
		~ACamera()noexcept;
		static std::string includeClassID(std::string data, int CID);
	public:
		void setScene(std::shared_ptr<DDD::Scene> s)noexcept;
		void move(const cgtools::point& newPos) noexcept;
		void setAngle(const double& newAngle) noexcept;
		virtual void init()noexcept = 0;
		// Geerbt über ISerializable
		std::string serialize() const override;
		void load(std::string serialized)override;
		static std::shared_ptr<DDD::ACamera> createFromSerialization(std::string data);
		size_t size()const override;
		//void setScene(std::shared_ptr<DDD::Scene>& s);
	};
}


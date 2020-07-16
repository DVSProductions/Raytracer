#pragma once
#include <memory>
#include "Ray.h"
#include "Scene.h"
#include "../cgtools/point.h"
#include "../cgtools/Renderer.h"
#include "../cgtools/ISerializable.h"
namespace DDD {
	class ACamera :public cgtools::Renderer, public ISerializable {
	protected:
		uint_fast16_t reflectionDepth = 1;
		std::shared_ptr<DDD::Scene> scene;
		cgtools::point position;
		double angle;
		ACamera(const double& angle) noexcept;
		ACamera(const cgtools::point& pos, const double& angle) noexcept;
		static std::string includeClassID(std::string data, int CID);
	public:
		~ACamera()noexcept;
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


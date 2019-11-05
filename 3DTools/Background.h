#pragma once
#include <renderable.h>
#include <Hit.h>
namespace DDD {
	class Background : public renderable {
		cgtools::Color c;
		friend class renderable;
		friend class PinholeCamera;
		Background(std::string serialized);
	public:
		static const int CLASSID = -1;
		Background(cgtools::Color color)noexcept;
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		std::string serializeFast()const;
		void load(std::string serialized) override;
		Background operator=(const Background& b)noexcept;

	};
}


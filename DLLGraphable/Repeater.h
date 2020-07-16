#pragma once
#include "generator.h"
#include "../cgtools/point.h"
#include "../cgtools/Translation.h"

namespace DDD {
	class Repeater :public Generator {
		friend class Generator;
		static const int CLASSID = 1;
		cgtools::point position = cgtools::point(0);
		cgtools::vector offset = cgtools::point(0);
		double steplimit, stepsize;
		Repeater(std::string serialized);
	public:
		renderable* evaluate(uint64_t startSeed)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const noexcept override;
	};
}
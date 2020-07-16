#pragma once
#include "generator.h"
namespace DDD {
	class Dice :public Generator {
		friend class Generator;
		static const int CLASSID = 0;
		Dice(std::string serialized);
	public:
		renderable* evaluate(uint64_t startSeed) const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const noexcept override;
	};
}

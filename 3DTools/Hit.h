namespace DDD {
	struct Hit;
}
#pragma once
#include "../cgtools/Color.h"
#include "../cgtools/point.h"
#include "Material.h"
#include <memory>
namespace DDD {
	struct Hit {
	public:
		std::shared_ptr<AMaterial> material;
		double t;
		cgtools::point pos;
		cgtools::direction n;
		bool hit;
		Hit()noexcept;
		Hit(double t, cgtools::point pos, cgtools::direction n, std::shared_ptr<AMaterial> m)noexcept;
		Hit(double t, cgtools::point pos, cgtools::direction n, cgtools::Color Material);
		cgtools::Color shade() const noexcept;
	};
}

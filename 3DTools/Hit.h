#pragma once
#include <Color.h>
#include <point.h>
using namespace cgtools;
namespace DDD {
	struct Hit {
	public:
		double t;
		point pos;
		direction n;
		Color c;
		bool hit;
		Hit(bool hit)noexcept;
		Hit(double t, point pos, direction n, Color c)noexcept;
		Color shade() const noexcept;
	};
}

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
		Hit(double t, point pos, direction n, Color c);
		Color shade() const noexcept;
	};
}

#pragma once
#include "vector.h"
#include "direction.h"
namespace cgtools {
	class direction;
	class point :
		public vector {
	public:
		point(double x, double y, double z) noexcept :vector(x, y, z) {}
		point operator-()noexcept;
		point operator-(const direction& d) noexcept;
		friend point operator+(const direction& d, const point& b)noexcept;
		friend point operator+(direction d, point b)noexcept;
		point operator+ (direction d) noexcept;
		direction todirection()noexcept;
		direction sub(const point& b)noexcept;
	};
}

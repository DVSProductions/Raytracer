#pragma once
#include "vector.h"
#include "direction.h"
#include <string>
namespace cgtools {
	class direction;
	class point : public vector {
		friend class direction;
	public:
		operator std::string()const;
		point(vector v)noexcept :vector(v.x, v.y, v.z) {}
		point(double uniform) noexcept :vector(uniform, uniform, uniform) {}
		point(double x, double y, double z) noexcept :vector(x, y, z) {}
		point operator-()noexcept;
		point operator-(const point& p) const noexcept;
		point operator-(const direction& d) noexcept;
		//point operator+(const direction& d, const point& b)noexcept;
		//point operator+(direction d, point b)noexcept;
		point operator+ (const direction& d) const noexcept;
		direction todirection()noexcept;
		direction sub(const point& b)noexcept;
		point operator*(const vector& s)const noexcept;
		direction operator/(const double& d) const noexcept;
		size_t size()const override;
	};
}

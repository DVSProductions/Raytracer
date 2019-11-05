#pragma once
#include "vector.h"
#include "direction.h"
#include <msxml.h>
#include <string>
namespace cgtools {
	class direction;
	class point :
		public vector {
	public:
		operator std::string()const {
			return "(point[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "])";
		}
		point(vector v)noexcept :vector(v.x, v.y, v.z) {}
		point(double uniform) noexcept:vector(uniform, uniform, uniform){}
		point(double x, double y, double z) noexcept :vector(x, y, z) {}
		point operator-()noexcept;
		point operator-(const point& p) const noexcept;
		point operator-(const direction& d) noexcept;
		friend point operator+(const direction& d, const point& b)noexcept;
		friend point operator+(direction d, point b)noexcept;
		point operator+ (const direction& d) const noexcept;
		direction todirection()noexcept;
		direction sub(const point& b)noexcept;
		point operator*(const vector& s)const noexcept;
	};
}

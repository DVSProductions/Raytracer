#pragma once
#include "vector.h"
#include "point.h"
#include "Color.h"
namespace cgtools {
	class point;
	class direction : public vector {
		friend class point;
	public:
		operator std::string()const;
		direction operator+(const direction& b) const noexcept;
		direction(double x, double y, double z) noexcept;
		direction operator-(const direction& b)const noexcept;
		direction operator-()const noexcept;
		direction operator*(const point& v) const noexcept;
		direction operator*(const double& s)const noexcept;
		friend direction operator*(const double& s, const direction& a)noexcept;
		direction operator/(const double& s) const noexcept;
		/// <summary>
		/// Cross product
		/// </summary>
		direction operator|(const direction& b) const noexcept;
		/// <summary>
		/// normalized
		/// </summary>
		/// <returns></returns>
		direction operator~()const noexcept;
		point operator+(const point & p)const noexcept;
		point operator+(point p)const noexcept ;
		size_t size()const override;
	};
}
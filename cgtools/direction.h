#pragma once
#include "vector.h"
#include "point.h"
#include "Color.h"
class direction : public vector {
public:
	direction operator+(const direction& b) noexcept;
	direction(double x, double y, double z)noexcept;
	direction operator-(const direction &b) noexcept;
	direction operator*(const double &s)noexcept;
	friend direction operator*(const double& s, const direction& a)noexcept;
	direction operator/(const double &s)noexcept;
	/// <summary>
	/// Cross product
	/// </summary>
	direction operator|(const direction &b)noexcept;
	direction operator~()noexcept;
	Color shade(const Color &c)noexcept;
};
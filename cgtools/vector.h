#pragma once
#include <math.h>
class vector {
protected:
	vector(double x, double y, double z)noexcept :x(x), y(y), z(z) {}
public:
	const double x, y, z;
	vector operator-() noexcept;
	/// <summary>
	/// length
	/// </summary>
	double operator!() noexcept;
	inline double length()noexcept { return !this; }
	double squaredLength()noexcept;
	bool operator==(const vector &a)noexcept;
	/// <summary>
	/// Dot product
	/// </summary>
	/// <param name="b"></param>
	double operator[](const vector &b)noexcept;
};


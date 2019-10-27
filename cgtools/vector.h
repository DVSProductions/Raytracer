#pragma once
#include <math.h>
#include <cstdint>
namespace cgtools {
	class vector {
	protected:
		vector(double x, double y, double z)noexcept :x(x), y(y), z(z) {}
	public:
		double x, y, z;
		vector operator-(const double& d)const noexcept;
		vector operator-() const  noexcept;
		/// <summary>
		/// length
		/// </summary>
		double operator!() const noexcept;
		inline double length() const noexcept { return !this; }
		double squaredLength() const noexcept;
		bool operator==(const vector& a) const noexcept;
		/// <summary>
		/// Dot product
		/// </summary>
		/// <param name="b"></param>
		double operator[](const vector& b) const noexcept;
		/// <summary>
		/// Index 0-2. Abstraction for x,y,z
		/// </summary>
		/// <param name="b"></param>
		/// <returns></returns>
		double operator[](const int& b) const noexcept;
		double scalar(const vector& v) const noexcept;
		vector reduceAccuracy(uint8_t power)const noexcept;
	};
}
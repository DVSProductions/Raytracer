#pragma once
#include "vector.h"
#include "point.h"
#include "Color.h"
namespace cgtools {
	class direction : public vector {
	public:
		operator std::string()const{
			return "(direction[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "])";
		}
		direction operator+(const direction& b) const noexcept;
		direction(double x, double y, double z) noexcept;
		direction operator-(const direction& b)const noexcept;
		direction operator*(const double& s)const noexcept;
		direction operator*(const vector& s)const noexcept;
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
		direction operator~()noexcept;
		//std::string serialize()const override;
		//void load(std::string serialized) override;
	};
}
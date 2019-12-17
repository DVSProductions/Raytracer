#pragma once
#include "ComplexRotation.h"
namespace cgtools {
	class Rotation :public ComplexRotation {
	protected:
		friend class ATransformation;
		const static int CLASSID = 1;
		static direction axisToDirection(uint8_t axis)noexcept;
		uint8_t axis;
		double angle;
		Rotation(std::string str);
	public:
		Rotation(uint8_t axis, double angle) noexcept;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
	};
}
#pragma once
#include "ATransformation.h"
namespace cgtools {
	enum class Axis:int16_t { x = 0, y = 1, z = 2 };
	class Rotation :public ATransformation {
	protected:
		friend class ATransformation;
		const static int CLASSID = 1;
		//static direction axisToDirection(int16_t axis)noexcept;
		Axis axis;
		double angle = 0;
	public:
		Rotation(std::string str);
		Rotation(Axis axis, double angle) noexcept;
		matrix operator()() const noexcept;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
	};
}
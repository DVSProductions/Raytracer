#pragma once
#include "ATransformation.h"
namespace cgtools {
	class ComplexRotation :public ATransformation {
	protected:
		friend class ATransformation;
		const static int CLASSID = 3;
		direction caxis;
		double angle;
		ComplexRotation(std::string str);
	public:
		ComplexRotation(direction axis, double angle) noexcept;
		matrix operator()()const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
	};
}
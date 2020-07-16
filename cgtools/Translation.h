#pragma once
#include "ATransformation.h"
namespace cgtools {
	class Translation :	public ATransformation {
	protected:
		const static int CLASSID = 0;
		vector offset;
		friend class ATransformation;
	public:
		Translation(std::string str);
		Translation(vector offset)noexcept;
		matrix operator()()const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
		vector getOffset()const noexcept;
	};
}


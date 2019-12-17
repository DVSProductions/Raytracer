#pragma once
#include "ATransformation.h"
namespace cgtools {
	class Translation :	public ATransformation {
	protected:
		const static int CLASSID = 0;
		vector offset;
		friend class ATransformation;
		Translation(std::string str);
	public:
		Translation(vector offset);
		matrix operator()()const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
	};
}


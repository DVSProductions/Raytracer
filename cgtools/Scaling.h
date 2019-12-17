#pragma once
#include "ATransformation.h"
namespace cgtools {
	class Scaling :
		public ATransformation {
	protected:
		friend class ATransformation;
		const static int CLASSID = 2;
		vector factors;
		Scaling(std::string str);
	public:
		Scaling(vector factors);
		matrix operator()()const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
	};
}


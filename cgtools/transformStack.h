#pragma once
#include "Matrix.h"
#include "ISerializable.h"
#include "ATransformation.h"
#include <vector>
namespace cgtools {
	class transformStack : ISerializable{
		std::vector<ATransformation *> children;		
	public:
		matrix operator()() noexcept;
		void add(ATransformation* t);
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const override;
		transformStack clone()const noexcept;
	};

}


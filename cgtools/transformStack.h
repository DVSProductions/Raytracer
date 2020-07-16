#pragma once
#include "Matrix.h"
#include "ISerializable.h"
#include "ATransformation.h"
#include <vector>
namespace cgtools {
	class transformStack : ISerializable{
		std::vector<std::shared_ptr<ATransformation>> children;		
	public:
		transformStack() = default;
		transformStack(std::string serialized);
		matrix operator()() noexcept;
		void add(std::unique_ptr<ATransformation> t) noexcept;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const override;
		transformStack clone()const noexcept;
	};

}


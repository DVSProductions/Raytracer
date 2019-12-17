#pragma once
#include "Matrix.h"
#include "ISerializable.h"
namespace cgtools {
	class ATransformation : public ISerializable {
	protected:
		static std::string includeClassID(std::string data, int CID);
	public:
		virtual matrix operator()() const noexcept = 0 ;
		static ATransformation* createFromSerialization(std::string data);
	};
}

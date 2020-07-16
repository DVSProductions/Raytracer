#pragma once
#include "../cgtools/point.h"
#include "Hit.h"
#include "Ray.h"
#include "../cgtools/ISerializable.h"

namespace DDD {
	//extern int typeids[];
	class renderable : public ISerializable {
	protected:
		renderable(cgtools::point position) noexcept;
		renderable(std::string serialized);
		static std::string includeClassID(std::string data, int CID);
	public:
		cgtools::point p;
		virtual Hit intersect(Ray r)const = 0;
		static renderable* createFromSerialization(std::string data);
		virtual renderable* clone() const = 0;
	};
}


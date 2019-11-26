namespace DDD {
	class AMaterial;
}
#pragma once
#include "../cgtools/direction.h"
#include "../cgtools/Color.h"
#include "../cgtools/ISerializable.h"
#include "Hit.h"
#include "Ray.h"
#include <random>
#include "Ziggurat.hpp"

#define MaterialSplitter "}"

#define useMT true
namespace DDD {
	class AMaterial : public ISerializable {
	protected:
		AMaterial() noexcept;
		cxx::ziggurat_normal_distribution<double> dist;
#if useMT
		std::mt19937_64 mt;
#else
		std::ranlux48_base mt;
#endif
	public:
		double scatterFactor = 0;
		cgtools::Color emission;
		cgtools::Color albedo;
		AMaterial(cgtools::Color emi, cgtools::Color alb);
		virtual Ray scatteredRay(DDD::Hit origin, DDD::Ray originalRay) = 0;
		static std::string includeClassID(std::string data, int CID);
		static AMaterial* createFromSerialization(std::string data);
		virtual AMaterial* clone() const = 0;
		void operator=(const AMaterial& para) noexcept;
	};
}

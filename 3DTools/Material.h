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
#define useRandfast 1
#if useRandfast
#include "../cgtools/randfast.h"
#define RNG() dist.apply()
#else
#include "Ziggurat.hpp"
#define RNG() dist(mt)
#endif

#define MaterialSplitter "}"

namespace DDD {
	class AMaterial : public ISerializable {
	protected:
		AMaterial() noexcept;
#if useRandfast
		randfast dist;
		void initRandom(double min, double max);
#else
		void initRandom(double average, double diviation);
		std::mt19937_64 mt;
		cxx::ziggurat_normal_distribution<double> dist;
#endif
		void initRandom(double roughness);
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

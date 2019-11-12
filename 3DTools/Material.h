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
namespace DDD {
	class AMaterial : public ISerializable {
	protected:
		AMaterial();
		std::normal_distribution<double> dist;
		std::mt19937 mt;
	public:
		double scatterFactor;
		cgtools::Color emission;
		cgtools::Color albedo;
		AMaterial(cgtools::Color emi, cgtools::Color alb);
		virtual Ray scatteredRay(DDD::Hit origin, DDD::Ray originalRay) = 0;
		static std::string includeClassID(std::string data, int CID);
		static AMaterial* createFromSerialization(std::string data);
		virtual AMaterial* clone() const = 0;
		void operator=(const AMaterial& para);
	};


	class Vanta :public AMaterial {
		friend class AMaterial;
		static const int CLASSID = 0;
		Vanta(std::string serialized);
	public:
		Vanta(cgtools::Color Material);
		Ray scatteredRay(Hit origin, Ray originalRay)override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const;
		size_t size()const override;
	};


	class Mirror :public  AMaterial {
		friend class AMaterial;
		static const int CLASSID = 1;
		Mirror(std::string serialized);
	public:
		Mirror(cgtools::Color Material);
		Mirror(cgtools::Color Emi, cgtools::Color Albe);
		Ray scatteredRay(Hit origin, Ray originalRay)override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const;
		size_t size()const override;
	};


	class Chalk :public AMaterial {
		friend class AMaterial;
		static const int CLASSID = 2;
		Chalk(std::string serialized);
	public:
		Chalk(cgtools::Color Emi, cgtools::Color alb);
		Ray scatteredRay(Hit origin, Ray originalRay)override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const;
		size_t size()const override;
	};
}

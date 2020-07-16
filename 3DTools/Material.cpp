#include "Material.h"
#include <stdexcept>
#include "Glass.h"
#include "Metal.h"
#include "LightSource.h"
#include "Mirror.h"
#include "Chalk.h"
#include "Vanta.h"
#define deserial(Material) case Material::CLASSID: return new Material(s.at(1))
namespace DDD {
	uint64_t progressiveEmergencySeed = 0;
#if useRandfast
	void AMaterial::initRandom(double min, double max) noexcept{
		try {
			dist = randfast(std::mt19937_64(std::random_device()())(), min, max);
		}
		catch (...) {
			dist = randfast(++progressiveEmergencySeed);
		}
	}
	void AMaterial::initRandom(double roughness)noexcept {
#if useRandfast
		initRandom(-roughness, roughness);
#else
		initRandom(0, roughness / 2);
#endif
	}
	AMaterial::AMaterial()noexcept : dist(0) {}
#else
	AMaterial::AMaterial() {
		std::random_device rd;
		mt = std::mt19937_64(rd());
	}
	void initRandom(double average, double diviation) {
		dist = cxx::ziggurat_normal_distribution<double>(average, diviation);

	}
#endif

	AMaterial::AMaterial(cgtools::Color emi, cgtools::Color alb)noexcept : AMaterial()  {
		emission = emi;
		albedo = alb;
	}
	std::string DDD::AMaterial::includeClassID(std::string data, int CID) {
		return std::to_string(CID) + "#" + data;
	}

	DDD::AMaterial* DDD::AMaterial::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "#");
		if (s.size() == 0 || s.size() == 1)
			return new Vanta(data);
		int n = -1;
		f_chars(s.at(0), n);
		switch (n) {
			deserial(Vanta);
			deserial(Mirror);
			deserial(Chalk);
			deserial(LightSource);
			deserial(Metal);
			deserial(Glass);
		}
		return nullptr;
	}

	void AMaterial::operator=(const AMaterial& para) noexcept {
		scatterFactor = para.scatterFactor;
		emission = para.emission;
		albedo = para.albedo;
	}
}
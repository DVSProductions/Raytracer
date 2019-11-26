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
	AMaterial::AMaterial() noexcept {
		std::random_device rd;
#if useMT
		mt = std::mt19937_64(rd());
#else
		mt = std::ranlux48_base(rd());
#endif
	}
	AMaterial::AMaterial(cgtools::Color emi, cgtools::Color alb) {
		emission = emi;
		albedo = alb;
	}
	std::string DDD::AMaterial::includeClassID(std::string data, int CID) {
		return std::string();
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
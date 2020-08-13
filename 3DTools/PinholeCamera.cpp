#include "../DLLFiles/DLLInfo.h"
#include "PinholeCamera.h"
#include <stdint.h>
namespace DDD {
	PinholeCamera::PinholeCamera(std::string serialized) :ACamera(0), background(cgtools::Color(0, 0, 0)) {
		this->load(serialized);
	}
	PinholeCamera::PinholeCamera() : ACamera(0), background(cgtools::c_black) {}
	PinholeCamera::PinholeCamera(double angle, Background background)noexcept :ACamera(angle), background(background) {
		init();
	}

	PinholeCamera::PinholeCamera(double angle, Background background, unsigned short reflectionDepth) noexcept : PinholeCamera(angle, background) {
		this->reflectionDepth = reflectionDepth;
		try {
			eStack = std::vector<cgtools::Color>(reflectionDepth);//std::make_unique<cgtools::Color[]>(reflectionDepth);
			aStack = std::vector<cgtools::Color>(reflectionDepth);//std::make_unique<cgtools::Color[]>(reflectionDepth);
		}
		catch (...) {}
	}

	void PinholeCamera::init() noexcept {
		w0_5 = width / 2.0;
		h0_5 = height / 2.0;
		a05tan = tan(angle / 2.0);
		zpre = -(w0_5 / a05tan);
	}
#ifdef _HUGE_ENUF
#undef INFINITY
#define INFINITY   static_cast<float>(_HUGE_ENUF * _HUGE_ENUF)
#endif
	Ray PinholeCamera::generateRay(double x, double y)noexcept {
		return Ray(cgtools::point(0, 0, 0), ~cgtools::direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0.0);
	}
	cgtools::Color PinholeCamera::getColor(double x, double y) {
		auto r = generateRay(x, y);
		eStack.clear();
		aStack.clear();
		cgtools::Color ret = cgtools::c_black;
		for (uint_fast16_t n = 0; n != reflectionDepth; n++) {
			const auto h = scene->intersect(r);
			if (h.hit == false) {
				ret = this->background.Material->emission;
				break;
			}
			else if (h.material->albedo == cgtools::c_black) {
				ret = h.material->emission;
				if (reflectionDepth == 1)return h.shade();
				break;
			}
			eStack.push_back(h.material->emission);
			aStack.push_back(h.material->albedo);
			r = h.material->scatteredRay(h, r);
		}
		for (auto e = eStack.begin(), a = aStack.begin(), end = eStack.end(); e != end; ++e, ++a)
			ret = *e + *a * ret;
		return ret;
		//return h.hit ? h.shade() : background.intersect(r).c;
	}

	std::string PinholeCamera::serialize() const {
		return ACamera::includeClassID(background.serializeFast() + "[" + ACamera::serialize() + "[", CLASSID);
	}

	void PinholeCamera::load(std::string serialized) {
		const auto s = Serializable::split(serialized, "[");
		background.load(s.at(0));
		ACamera::load(s.at(1));
		eStack.clear();
		eStack.reserve(reflectionDepth);
		aStack.clear();
		aStack.reserve(reflectionDepth);
	}

	size_t PinholeCamera::size() const {
		return sizeof(PinholeCamera) + ACamera::size() - sizeof(ACamera);
	}
	std::shared_ptr <cgtools::Renderer > PinholeCamera::clone() {
		auto ret = std::make_shared<PinholeCamera>(angle, background, reflectionDepth);
		if (this->scene)
			ret->setScene(this->scene);
		return ret;
	}
}
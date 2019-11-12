#include "DLLInfo.h"
#include "PinholeCamera.h"
#include <stack>
namespace DDD {
	PinholeCamera::PinholeCamera(std::string serialized) :ACamera(cgtools::point(0, 0, 0), 0), background(cgtools::Color(0, 0, 0)) {
		this->load(serialized);
	}
	PinholeCamera::PinholeCamera(double angle, const cgtools::point& position, Background background)noexcept :ACamera(position, angle), background(background) {
		precalculation(angle);
		this->background = background;
	}

	PinholeCamera::PinholeCamera(double angle, const cgtools::point& position, Background background, unsigned short reflectionDepth) noexcept : PinholeCamera(angle, position, background) {
		this->reflectionDepth = reflectionDepth;
	}

	void PinholeCamera::init() noexcept {
		w0_5 = width / 2.0;
		h0_5 = height / 2.0;
		a05tan = tan(angle / 2.0);
		zpre = -(w0_5 / a05tan);
	}

	void PinholeCamera::precalculation(double angle)noexcept {
		init();
	}

	Ray PinholeCamera::generateRay(double x, double y)noexcept {
		return Ray(position, ~cgtools::direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0);
	}
	cgtools::Color PinholeCamera::getColor(double x, double y) {
		auto r = generateRay(x, y);
		//const auto h = scene->intersect(r);
		std::stack<cgtools::Color> eStack;
		std::stack<cgtools::Color> aStack;
		cgtools::Color ret = cgtools::c_black;
		for (size_t n = 0; n != reflectionDepth; n++) {
			auto h = scene->intersect(r);
			if (h.hit == false) {
				ret = this->background.Material->emission;
				break;
			}
			else if (h.material->albedo == cgtools::c_black) {
				ret = h.material->emission;
				if (reflectionDepth == 1)return h.shade();
				break;
			}
			eStack.push(h.material->emission);
			aStack.push(h.material->albedo);
			r = h.material->scatteredRay(h, r);
		}
		while (!eStack.empty()) {
			ret = eStack.top() + aStack.top() * ret;
			eStack.pop();
			aStack.pop();
		}
		return ret;
		//return h.hit ? h.shade() : background.intersect(r).c;
	}

	std::string PinholeCamera::serialize() const {
		return ACamera::includeClassID(background.serializeFast() + "[" + __super::serialize() + "[", CLASSID);
	}

	void PinholeCamera::load(std::string serialized) {
		const auto s = Serializable::split(serialized, "[");
		background.load(s.at(0));
		__super::load(s.at(1));
	}

	size_t PinholeCamera::size() const {
		return sizeof(PinholeCamera) + __super::size() - sizeof(ACamera);
	}

}
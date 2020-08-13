#include "../DLLFiles/DLLInfo.h"
#include "MovablePinholeCamera.h"
namespace DDD {
	MovablePinholeCamera::MovablePinholeCamera(std::string serialized) :PinholeCamera() {
		this->load(serialized);
	}
	MovablePinholeCamera::MovablePinholeCamera(double angle, Background background)noexcept :PinholeCamera(angle, background) {}

	MovablePinholeCamera::MovablePinholeCamera(double angle, Background background, unsigned short reflectionDepth) noexcept : MovablePinholeCamera(angle, background) {
		this->reflectionDepth = reflectionDepth;
		try {
			eStack = std::vector<cgtools::Color>(reflectionDepth);
			aStack = std::vector<cgtools::Color>(reflectionDepth);
		}
		catch (...) {}
	}
	MovablePinholeCamera::MovablePinholeCamera(double angle, Background background, unsigned short reflectionDepth, cgtools::transformStack stack) noexcept : MovablePinholeCamera(angle, background, reflectionDepth) {
		transformation = stack();
	}

	void MovablePinholeCamera::init() noexcept {
		PinholeCamera::init();
		//transformation = ts();
		newCenter = transformation * cgtools::point(0, 0, 0);
	}
	Ray MovablePinholeCamera::generateRay(double x, double y)noexcept {
		return Ray(newCenter, transformation * (~cgtools::direction(x - w0_5, h0_5 - y, zpre)), INFINITY, 0);
	}

	cgtools::Color MovablePinholeCamera::getColor(double x, double y) {
		auto r = generateRay(x, y);
		eStack.clear();
		aStack.clear();
		cgtools::Color ret = cgtools::c_black;
		for (uint_fast16_t n = 0; n != reflectionDepth; n++) {
			//r = r.transform(transformation);
			const auto h = scene->intersect(r);
			if (reflectionDepth == 1)return cgtools::Color((1 + h.n.x) / 2, (1 + h.n.y) / 2, (1 + h.n.z) / 2);// h.shade();
			if (h.hit == false) {
				ret = this->background.Material->emission;
				break;
			}
			else if (h.material->albedo == cgtools::c_black) {
				ret = h.material->emission;
				if (reflectionDepth == 1)return cgtools::Color(h.n.x, h.n.y, h.n.z);// h.shade();
				break;
			}
			eStack.push_back(h.material->emission);
			aStack.push_back(h.material->albedo);
			r = h.material->scatteredRay(h, r);
		}
		for (auto e = eStack.begin(), a = aStack.begin(), end = eStack.end(); e != end; ++e, ++a)
			ret = *e + *a * ret;
		return ret;
	}

	std::string MovablePinholeCamera::serialize() const {
		//return ACamera::includeClassID(background.serializeFast() + "[" + ACamera::serialize() + "[" + ts.serialize() + "[", CLASSID);
		return "";
	}

	void MovablePinholeCamera::load(std::string serialized) {
		const auto s = Serializable::split(serialized, "[");
		PinholeCamera::load(serialized);
		transformation = cgtools::transformStack(s.at(2))();
		init();
	}

	size_t MovablePinholeCamera::size() const {
		return sizeof(MovablePinholeCamera) + ACamera::size() - sizeof(ACamera);
	}
	std::shared_ptr <cgtools::Renderer > MovablePinholeCamera::clone() {
		auto ret = std::make_shared<MovablePinholeCamera>(angle, background, reflectionDepth);
		if (this->scene)
			ret->setScene(this->scene);
		ret->transformation = transformation;
		ret->init();
		return ret;
	}
}
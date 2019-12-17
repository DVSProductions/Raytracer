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
			eStack = std::make_unique<cgtools::Color[]>(reflectionDepth);
			aStack = std::make_unique<cgtools::Color[]>(reflectionDepth);
		}
		catch (...) {}
	}
	MovablePinholeCamera::MovablePinholeCamera(double angle, Background background, unsigned short reflectionDepth, cgtools::transformStack stack) noexcept : MovablePinholeCamera(angle, background, reflectionDepth) {
		ts = stack;
	}

	void MovablePinholeCamera::init() noexcept {
		PinholeCamera::init();
		transformation = ts();
		newCenter = transformation * cgtools::point(0, 0, 0);
	}
	Ray MovablePinholeCamera::generateRay(double x, double y)noexcept {
		return Ray(newCenter, transformation * (~cgtools::direction(x - w0_5, h0_5 - y, zpre)), INFINITY, 0);
	}

	cgtools::Color MovablePinholeCamera::getColor(double x, double y) {
		auto r = generateRay(x, y);
		int_fast32_t StackSize = 0;
		cgtools::Color ret = cgtools::c_black;
		for (uint_fast16_t n = 0; n != reflectionDepth; n++) {
			//r = r.transform(transformation);
			const auto h = scene->intersect(r);
			if (h.hit == false) {
				ret = this->background.Material->emission;
				break;
			}
			else if (h.material->albedo == cgtools::c_black) {
				ret = h.material->emission;
				if (reflectionDepth == 1)return cgtools::Color(h.n.x,h.n.y,h.n.z);// h.shade();
				break;
			}
			eStack[StackSize] = h.material->emission;
			aStack[StackSize++] = h.material->albedo;
			r = h.material->scatteredRay(h, r);
		}
		while (--StackSize != -1)
			ret = eStack[StackSize] + aStack[StackSize] * ret;
		return ret;
	}

	std::string MovablePinholeCamera::serialize() const {
		return ACamera::includeClassID(background.serializeFast() + "[" + ACamera::serialize() + "[" + ts.serialize() + "[", CLASSID);
	}

	void MovablePinholeCamera::load(std::string serialized) {
		const auto s = Serializable::split(serialized, "[");
		PinholeCamera::load(serialized);
		ts.load(s.at(2));
		init();
	}

	size_t MovablePinholeCamera::size() const {
		return sizeof(MovablePinholeCamera) + ACamera::size() - sizeof(ACamera) + ts.size();
	}
	std::shared_ptr <cgtools::Renderer > MovablePinholeCamera::clone() {
		auto ret = std::make_shared<MovablePinholeCamera>(angle, background, reflectionDepth, ts.clone());
		ret->setScene(this->scene);
		ret->init();
		return ret;
	}
}
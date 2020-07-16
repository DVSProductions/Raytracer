#include "Group.h"
#include "../cgtools/Anybase.h"
namespace DDD {
	Group::Group(const Group& g) :Group(g.p) {
		for (auto e : g.objects) {
			objects.push_back(e->clone());
		}
	}
	Group Group::GroupClone() {
		Group ret(p);
		const auto end = objects.end();
		for (auto it = objects.begin(); it != end; it++)
			ret.addObject((*it)->clone());
		return ret;
	}
	Group::Group() noexcept :renderable(cgtools::point(0, 0, 0)) {}
	Group::Group(std::string serialized) : Group() {
		load(serialized);
	}

	Group::Group(cgtools::point position) : renderable(position) {
		objects = std::vector <renderable*>();
	}

	Group::~Group() { clear(); }

	void Group::addObject(renderable* obj) {
		objects.push_back(obj);
	}

	void Group::clear()noexcept {
		try {
			const auto end = objects.size();
			for (size_t n = 0; n != end; n++)
				delete[](objects.at(n));
			objects.clear();
		}
		catch (...) {
			try {
				objects.clear();
			}
			catch (...) {
			}
		}
	}

	Hit Group::intersect(Ray r) const {
		Hit closest = Hit();
		const auto movedRay = Ray(transform * r.x0, transform * r.dir, r.tmax, r.tmin);
		const auto offsetRay = Ray(movedRay.x0 - p, movedRay.dir, movedRay.tmax, movedRay.tmin);
		const auto end = objects.end();
		for (auto it = objects.begin(); it != end; it++) {
			const auto h = (*it)->intersect(offsetRay);
			if (h.hit && (!closest.hit || h.t < closest.t))
				closest = h;
		}
		if (closest.hit)
			closest = Hit(closest.t, transformBack * closest.pos, transformBack * closest.n, closest.material);
		return closest;
	}
	uint_fast64_t Group::serializationIDs = 0;
	std::string Group::serialize() const {
		//const size_t siz = this->objects->size();
		auto delim = "°" + Anybase::ConvertB64(++serializationIDs);
		std::string ret = this->p.serialize()
			+ "$"
			+ delim
			+ "$" + delim;
		for (auto e : objects)
			ret += e->serialize() + delim;
		serializationIDs--;
		return includeClassID(ret, CLASSID);
	}

	void Group::load(std::string serialized) {
		const auto ch = Serializable::split(serialized, "$");
		this->p.load(ch.at(0));
		const auto delim = ch.at(1);
		const auto children = Serializable::split(serialized, delim);
		const auto siz = children.size();
		this->clear();
		for (size_t n = 1; n < siz; n++)
			objects.push_back(renderable::createFromSerialization(children.at(n)));
	}

	renderable* Group::clone() const {
		const auto ret = new Group(p);
		const auto end = objects.end();
		for (auto it = objects.begin(); it != end; it++)
			ret->addObject((*it)->clone());
		return ret;
	}

	size_t Group::size() const {
		size_t result = sizeof(Group);
		for (auto e : objects)
			result += e->size();
		return result;
	}
	void Group::setTransform(cgtools::matrix EvaluatedTransform) noexcept {
		transform = EvaluatedTransform;
		try {
			transformBack = !EvaluatedTransform;
		}
		catch (...) {}
		transformTransposed = ~transformBack;
	}
}
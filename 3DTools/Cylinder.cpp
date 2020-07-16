#include "Cylinder.h"
#include "Plane.h"
#include "Pipe.h"
namespace DDD {
	Cylinder::Cylinder(std::string serialized) :Group(cgtools::point(0, 0, 0)) {
		load(serialized);
	}
	void Cylinder::makeChildren() {
		addObject(new Plane(cgtools::point(p.x, (p.y - height / 2), p.z), cgtools::direction(0, -1, 0), material, radius));
		addObject(new Plane(cgtools::point(p.x, (p.y + height / 2), p.z), cgtools::direction(0, 1, 0), material, radius));
		addObject(new Pipe(p, radius, height,std::shared_ptr<AMaterial>(material->clone())));
	}
	Cylinder::Cylinder(cgtools::point position, double radius, double height, std::shared_ptr<AMaterial> mat) : Group(position), height(height), radius(radius) {
		this->material = mat;
		makeChildren();
	}
	std::string Cylinder::serialize() const {
		return includeClassID(std::to_string(radius) + "]" +std::to_string(height) + "]" + material->serialize() + "]" + p.serialize() + "]", CLASSID);
	}
	void Cylinder::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "]");
		f_chars(ret.at(0), radius);
		f_chars(ret.at(1), height);
		if (material != nullptr) material.reset();
		material = std::shared_ptr<AMaterial>(AMaterial::createFromSerialization(ret.at(2)));
		p.load(ret.at(3));
		clear();
		makeChildren();
	}
	renderable* Cylinder::clone() const {
		const auto ret = new Cylinder(p,radius, height,material);
		const auto end = objects.end();
		for (auto it = objects.begin(); it != end; it++)
			ret->addObject((*it)->clone());
		return ret;
	}
	size_t Cylinder::size() const noexcept {
		return sizeof(Cylinder)-sizeof(Group)+Group::size();
	}
}
#include "Repeater.h"
#include "../cgtools/point.h"
#include "../cgtools/Translation.h"
namespace DDD {
	Repeater::Repeater(std::string serialized) {
		load(serialized);
	}
	renderable* Repeater::evaluate(uint64_t startSeed)const {
		const auto ret = new Group(position);
		const auto offs = this->offset;
		if (steplimit > 0 && stepsize > 0) {
			for (double n = 0; n < steplimit; n += stepsize) {
				auto ng = new Group(cgtools::point(0));
				ng->setTransform(cgtools::Translation(cgtools::point(
					offs.x * n,
					offs.y * n,
					offs.z * n
				))());
				for (auto& child : children)
					ng->addObject(child->evaluate(++startSeed));
				ret->addObject(ng);
			}
		}
		else if (steplimit < 0 && stepsize < 0) {
			for (double n = 0; n > steplimit; n += stepsize) {
				auto ng = new Group(cgtools::point(0));
				ng->setTransform(cgtools::Translation(cgtools::point(
					offs.x * n,
					offs.y * n,
					offs.z * n
				))());
				for (auto& child : children)
					ng->addObject(child->evaluate(++startSeed));
				ret->addObject(ng);
			}
		}
		return ret;
	}
	std::string Repeater::serialize() const {
		return includeClassID(
			position.serialize() + "/" +
			offset.serialize() + "/" +
			std::to_string(steplimit) + "/" +
			std::to_string(stepsize) + "/", CLASSID);
	}
	void Repeater::load(std::string serialized) {
		const auto spl = Serializable::split(serialized, "/");
		position.load(spl.at(0));
		offset.load(spl.at(1));
		f_chars(spl.at(2), steplimit);
		f_chars(spl.at(3), stepsize);
	}
	size_t Repeater::size() const noexcept
	{
		return sizeof(Repeater);
	}
}
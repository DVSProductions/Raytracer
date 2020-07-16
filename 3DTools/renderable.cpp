#include "renderable.h"
/*PUT YOUR CLASSES BELOW AND IN THE SWITCH*/
#include "Sphere.h"
#include "Background.h"
#include "Plane.h"
#include "Group.h"
#include "Pipe.h"
#include "Cylinder.h"

#define deserial(Material) case Material::CLASSID: return new Material(s.at(1))
namespace DDD {
	renderable::renderable(cgtools::point position)noexcept :p(position) {}
	renderable::renderable(std::string serialized) : p(0, 0, 0) {
		p.load(serialized);
	}
	std::string renderable::includeClassID(std::string data, int CID) {
		return std::to_string(CID) + "!" + data + "!";
	}
	renderable* renderable::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "!");
		int n = -1;
		f_chars(s.at(0), n);
		switch (n) {
			deserial(Sphere);
			deserial(Background);
			deserial(Plane);
			deserial(Group);
			deserial(Pipe);
			deserial(Cylinder);
		}
		return nullptr;
	}
}

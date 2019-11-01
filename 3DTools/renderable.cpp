#include "renderable.h"
/*PUT YOUR CLASSES BELOW AND IN THE DESCRIPTION*/
#include "Sphere.h"

namespace DDD {
	renderable::renderable(cgtools::point position)noexcept :p(position) {}
	renderable::renderable(std::string serialized) : p(0, 0, 0) {
		p.load(serialized);
	}
	std::string renderable::includeClassID(std::string data, int CID) {
		return std::to_string(CID) + "!" + data;
	}
	renderable* renderable::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "!");
		int n = -1;
		f_chars(s[0], n);
		renderable* ret = nullptr;
		switch (n) {
		case DDD_CLASS_SPHERE:
			ret = DDD_CLASS_SPHERE_DESERIALIZE(s[1]);
			break;
		}
		return ret;
	}
}

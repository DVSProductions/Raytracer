#include "renderable.h"
/*PUT YOUR CLASSES BELOW AND IN THE DESCRIPTION*/
#include "Sphere.h"
#define deserial(c,val) case c::CLASSID: return new c(val)
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
		f_chars(s.at(0), n);
		switch (n) {
			deserial(Sphere, s.at(1));
		}
		return nullptr;
	}
}

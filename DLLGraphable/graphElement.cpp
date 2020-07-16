#include "graphElement.h"
#include "generator.h"
#include "TransformElement.h"
#include "ShapeElement.h"
#include "GraphRoot.h"
#define deserial(elem) case elem::CLASSID: ret = new elem(s.at(2)); break;

namespace DDD {
	std::string GraphElement::includeClassID(std::string data, int CID) {
		return std::to_string(CID) + "@" + data + "@";
	}
	GraphElement* GraphElement::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "@");
		const auto idS = s.at(0);
		int id = -1;
		f_chars(idS, id);
		const auto addrS = s.at(1);
		uint64_t addr = 0;
		f_chars(addrS, addr);
		GraphElement* ret = nullptr;
		switch (id) {
		case Generator::CLASSID:
			ret = Generator::createFromSerialization(s.at(2));
			break;
			deserial(TransformElement);
			deserial(ShapeElement);
			deserial(GraphRoot);
		}
		if (ret != nullptr)
			ret->address = addr;
		return ret;
	}
}

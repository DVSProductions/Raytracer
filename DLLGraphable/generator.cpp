#include "generator.h"

/*PUT YOUR CLASSES BELOW AND IN THE SWITCH*/
#include "Dice.h"
#include "Repeater.h"

#define deserial(Gen) case Gen::CLASSID: return new Gen(s.at(1))
namespace DDD {
	std::string Generator::includeClassID(std::string data, int CID) {
		return GraphElement::includeClassID(std::to_string(CID) + "?" + data + "?", CLASSID);
	}
	Generator* Generator::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "?");
		const auto ns = s.at(0);
		int n = -1;
		f_chars(ns, n);
		switch (n) {
			deserial(Dice);
			deserial(Repeater);
		}
		return nullptr;
	}
}
#include "ATransformation.h"
#include "Translation.h"
#include "Scaling.h"
#include "Rotation.h"
#include "ComplexRotation.h"
#if _WIN64
#else
#include <stdexcept>
#endif
#define deserial(trans) case trans::CLASSID: return std::make_unique<trans>(s.at(1))
namespace cgtools {
	std::string ATransformation::includeClassID(std::string data, int CID) {
		return std::to_string(CID) + "#" + data + "#";
	}
	std::unique_ptr<ATransformation> ATransformation::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "#");
		int n = -1;
		f_chars(s.at(0), n);
		switch (n) {
			deserial(Translation);
			deserial(Rotation);
			deserial(Scaling);
			deserial(ComplexRotation);
		}
#if _WIN64
		throw std::exception(std::string("Unknown type :" + s.at(0)).c_str());
#else
throw std::runtime_error(std::string("Unknown type :" + s.at(0)).c_str());
#endif
	}
}
#pragma once
#include "graphElement.h"

namespace DDD {
	class Generator :public GraphElement {
		friend class GraphElement;
		static const int CLASSID = 0;
	protected:
		static std::string includeClassID(std::string data, int CID);
	public:
		static Generator* createFromSerialization(std::string data);
	};
}

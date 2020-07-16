#pragma once
#include "..\\cgtools\\ISerializable.h"
#include "..\\3DTools\\Group.h"
#include "../cgtools/Anybase.h"
#include <vector>
namespace DDD {
	class GraphElement :public ISerializable {
	private:
		friend class GraphRoot;
		uint64_t address;
		/*
		static uint_fast64_t serializationIDs;
	protected:
		static std::string reserveDelim() {
			return "^" + Anybase::ConvertB64(++serializationIDs) + "^";
		}
		static void freeDelim() {
			serializationIDs--;
		}*/
	protected:
		uint64_t seed;
		static std::string includeClassID(std::string data, int CID);
		std::vector<GraphElement*> children;
	public:
		virtual renderable* evaluate(uint64_t startSeed) const = 0;
		static GraphElement* createFromSerialization(std::string data);

	};
}

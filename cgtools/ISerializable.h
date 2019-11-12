#pragma once
#include <string>
#include <vector>
#include <charconv>
__interface ISerializable {
public:
	std::string serialize()const;
	void load(std::string serialized);
	size_t size()const;
};
#define f_chars(str,result) std::from_chars(str.data(), str.data() + str.size(), result)
namespace Serializable {
	std::vector<std::string> split(std::string s, std::string delim = "|");
}
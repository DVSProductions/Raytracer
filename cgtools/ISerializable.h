#pragma once
#include <string>
#include <vector>
#ifdef _WIN64 
#include <charconv>
#define f_chars(str,result) std::from_chars(str.data(), str.data() + str.size(), result)
#else
#define f_chars(str, result) _f_chars(str, &result);
void _f_chars(std::string str, double* result);
void _f_chars(std::string str, int* result);
void _f_chars(std::string str, long unsigned int* result);
#endif // 
class ISerializable {
public:
	virtual std::string serialize()const = 0;
	virtual void load(std::string serialized)=0;
	virtual size_t size()const=0;
};

namespace Serializable {
	std::vector<std::string> split(std::string s, std::string delim = "|");
}
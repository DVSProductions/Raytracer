#include "ISerializable.h"

std::vector<std::string> Serializable::split(std::string s, std::string delim) {
	size_t last = 0; size_t next = 0;
	std::vector<std::string> ret;
	const size_t delimlen = delim.length();
	while ((next = s.find(delim, last)) != std::string::npos) {
		ret.push_back(s.substr(last, next - last));
		last = next + delimlen;
	}
	return ret;
}
void _f_chars(std::string str, double* result) { *result = stod(str); }
void _f_chars(std::string str, int* result) { *result = stoi(str); }
void _f_chars(std::string str, long unsigned int* result) { *result = stol(str); }

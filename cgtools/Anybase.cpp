#include "Anybase.h"

std::streamoff Anybase::ssSize(std::stringstream& ss) {
	ss.seekg(0, std::ios::end);
	const auto ret = ss.tellg();
	ss.seekg(0, std::ios::beg);
	return ret;
}


std::string Anybase::Convert(uint_fast64_t num, uint_fast16_t b, const char charset[], int len) {
	std::stringstream s;
	while (num != 0) {
		s << charset[num % b];
		num /= b;
	}
	while (ssSize(s) < len) s << charset[0];
	return s.str();
}

std::string Anybase::Convert(uint_fast64_t num, uint_fast16_t b, const char charset[]) {
	std::stringstream s;
	while (num != 0) {
		s << charset[num % b];
		num /= b;
	}
	return s.str();
}

std::string Anybase::Convert(uint_fast64_t num, const char charset[]) {
	return Convert(num, static_cast<uint_fast16_t>(strlen(charset)), charset);
}
const char B64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::string Anybase::ConvertB64(uint_fast64_t num) {
	std::stringstream s;
	while (num != 0) {
		s << B64[num % 64u];
		num /= 64u;
	}
	return s.str();
}

std::string Anybase::ConvertB64(uint_fast64_t num, int len) {
	std::stringstream s;
	while (num != 0) {
		s << B64[num % 64u];
		num /= 64u;
	}
	while (ssSize(s) < len) s << '=';
	return s.str();
}

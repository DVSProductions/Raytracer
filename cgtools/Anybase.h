#pragma once
#include <string>
#include <sstream>
class Anybase {
	static std::streamoff ssSize(std::stringstream& ss);
public:
	/// <summary>
	/// Converts any number to a number in another base with given characters
	/// <para>
	///	Minimum length gets right padded with the first character in the charset
	/// </para>
	/// </summary>
	/// <param name="num">Number to convert</param>
	/// <param name="b">Base</param>
	/// <param name="charset">Set of characters to use</param>
	/// <param name="len">minimum length of the output</param>
	/// <returns></returns>
	static std::string Convert(uint_fast64_t num, uint_fast16_t b, const char charset[], int len);
	/// <summary>
	/// Converts any number to a number in another base with given characters
	/// </summary>
	/// <param name="num">Number to convert</param>
	/// <param name="b">Base</param>
	/// <param name="charset">Set of characters to use</param>
	/// <returns></returns>
	static std::string Convert(uint_fast64_t num, uint_fast16_t b, const char charset[]);
	/// <summary>
	/// Converts any number to a number in another base with given characters
	/// <para>
	/// Tries to automatically detect the current Base.
	/// Will fail if your charset contains '\0'
	/// </para>
	/// </summary>
	/// <param name="num">Number to convert</param>
	/// <param name="charset">Set of characters to use</param>
	/// <returns></returns>
	static std::string Convert(uint_fast64_t num, const char charset[]);
	static std::string ConvertB64(uint_fast64_t num);
	static std::string ConvertB64(uint_fast64_t num, int len);
};

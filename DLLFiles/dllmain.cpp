#include "DLLInfo.h"
#include "../cgtools/lodepng.h"
#include "../cgtools/cgtools.h"
/// <summary>
/// DEFINE THIS IN YOUR DLL
/// </summary>
bool workswitch(int Option);
#if _WIN64
/// <summary>
/// Converts a regular c-style string to a BSTR for usage in c#
/// </summary>
/// <param name="input">c_str to convert</param>
/// <returns></returns>
BSTR ANSItoBSTR(const char* input)noexcept {
	BSTR result = nullptr;
	const int lenA = lstrlenA(input);
	const int lenW = ::MultiByteToWideChar(CP_ACP, 0, input, lenA, nullptr, 0);
	if (lenW > 0) {
		result = ::SysAllocStringLen(nullptr, lenW);
		::MultiByteToWideChar(CP_ACP, 0, input, lenA, result, lenW);
	}
	return result;
}
#define SysAllocString(x) ::SysAllocString(x)
#else
BSTR ANSItoBSTR(const char* input)noexcept {
	return (char*)input;
#define SysAllocString(x) x
#define max(a,b) ((a)>(b)?(a):(b))
}

#endif // __WIN64
EXTERN_C_START
/// <summary>
/// Returns the current version of the DLL spec
/// </summary>
/// <returns></returns>
dll(BSTR) LibInfo(void) {
	return SysAllocString(ANSItoBSTR(libVersion.c_str()));
}
/// <summary>
/// Sends A list of files that will be created by this program
/// </summary>
/// <param name="idx">index in the array</param>
/// <returns></returns>
dll(BSTR) OutputFile(int idx) {
	return ANSItoBSTR(files[idx].c_str());
}
/// <summary>
/// Default Render Handler. Do Specific tasks in your workswitch
/// </summary>
/// <param name="Option">file index</param>
/// <param name="x">width</param>
/// <param name="y">height</param>
/// <returns></returns>
dll(bool) render(int Option, int x, int y) {
	width = x;
	height = y;
	scaling = max(width, height) / 160;
	try {
		return workswitch(Option);
	}
	catch (...) {
		return false;
	}
}
/// <summary>
/// returns result from 0-width
/// </summary>
dll(int) status() {
	//if (progress == width&&!joined) {
	//	joined = true;
	//	worker.join();
	//}
	return progress;
}
/// <summary>
/// returns the lodepng return value
/// </summary>
dll(int) returnValue() {
	return lodepngReturn;
}
/// <summary>
/// Turns a LodedPNG Error code to a Error message for displaying
/// </summary>
/// <param name="option">error code</param>
/// <returns></returns>
dll(BSTR) LodeReturnDecode(int errorCode) {
	return ANSItoBSTR(lodepng::lodepng_error_text(errorCode));
}
EXTERN_C_END
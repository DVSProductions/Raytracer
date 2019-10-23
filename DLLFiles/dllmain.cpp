#include "DllInfo.h"
#include <comutil.h>
#include "lodepng.h"
#include "cgtools.h"
/// <summary>
/// DEFINE THIS IN YOUR DLL
/// </summary>
bool workswitch(int Option);
//#include "Renderer1.cpp"
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

extern "C" {
	/// <summary>
	/// Returns the current version of the DLL spec
	/// </summary>
	/// <returns></returns>
	__declspec(dllexport) BSTR __cdecl LibInfo(void) {
		return ::SysAllocString(L"Library Version 1.0");
	}
	/// <summary>
	/// Sends A list of files that will be created by this program
	/// </summary>
	/// <param name="idx">index in the array</param>
	/// <returns></returns>
	__declspec(dllexport) BSTR __cdecl OutputFile(int idx) {
		return ANSItoBSTR(files[idx].c_str());
	}
	/// <summary>
	/// Default Render Handler. Do Specific tasks in your workswitch
	/// </summary>
	/// <param name="Option">file index</param>
	/// <param name="x">width</param>
	/// <param name="y">height</param>
	/// <returns></returns>
	__declspec(dllexport) bool render(int Option, int x, int y) {
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
	__declspec(dllexport) int status() {
		//if (progress == width&&!joined) {
		//	joined = true;
		//	worker.join();
		//}
		return progress;
	}
	/// <summary>
	/// returns the lodepng return value
	/// </summary>
	__declspec(dllexport) int returnValue() {
		return lodepngReturn;
	}
	/// <summary>
	/// Turns a LodedPNG Error code to a Error message for displaying
	/// </summary>
	/// <param name="option">error code</param>
	/// <returns></returns>
	__declspec(dllexport) BSTR LodeReturnDecode(int errorCode) {
		return ANSItoBSTR(lodepng_error_text(errorCode));
	}
}


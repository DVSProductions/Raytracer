#include "DllInfo.h"
#include <comutil.h>
#include "lodepng.h"
#include "cgtools.h"
bool workswitch(int Option);
//#include "Renderer1.cpp"
BSTR ANSItoBSTR(const char* input) {
	BSTR result = NULL;
	int lenA = lstrlenA(input);
	int lenW = ::MultiByteToWideChar(CP_ACP, 0, input, lenA, NULL, 0);
	if (lenW > 0) {
		result = ::SysAllocStringLen(0, lenW);
		::MultiByteToWideChar(CP_ACP, 0, input, lenA, result, lenW);
	}
	return result;
}

extern "C" {
	__declspec(dllexport) BSTR __cdecl LibInfo(void) {
		return ::SysAllocString(L"Library Version 1.0");
	}
	///Sends A list of files that will be created by this program
	__declspec(dllexport) BSTR __cdecl OutputFile(int idx) {
		return ANSItoBSTR(files[idx].c_str());
	}
	//bool joined = false;
	__declspec(dllexport) bool render(int Option, int x, int y) {
		//joined = false;
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
	/// 
	/// </summary>
	__declspec(dllexport) int returnValue() {
		return lodepngReturn;
	}
	__declspec(dllexport) BSTR LodeReturnDecode(int option) {
		return ANSItoBSTR(lodepng_error_text(option));
	}
}


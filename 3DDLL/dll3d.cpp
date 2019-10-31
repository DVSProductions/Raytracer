#include "3DInfo.h"
#include <comutil.h>
#include <string>

extern "C" {
	__declspec(dllexport) void setScene(const char* p) {
		playground->load(std::string(p));
	}
	__declspec(dllexport) void setCamera(const char* p) {
		cam->load(std::string(p));
	}
	__declspec(dllexport) void initialize3d() {
		prepare3d();
	}


}
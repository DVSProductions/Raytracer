#include "3DInfo.h"
#include <comutil.h>
#include <string>
#define dll(x) __declspec(dllexport) x __cdecl

EXTERN_C_START
dll(void) setScene(const char* p) {
	playground->load(std::string(p));
}
dll(void) setCamera(const char* p) {
	cam->load(std::string(p));
}
dll(void) initialize3d() {
	prepare3d();
}
dll(int) getSupportedClassesAt(int idx) {
	if (idx < 0)return -1;
	return supportedClasses[idx];
}

EXTERN_C_END
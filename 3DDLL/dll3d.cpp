#include "3DInfo.h"
#include <comutil.h>
#include <string>
#define dll(x) __declspec(dllexport) x __cdecl

extern BSTR ANSItoBSTR(const char* input)noexcept;
EXTERN_C_START
dll(void) setScene(const char* serializedData) {
	playground->load(std::string(serializedData));
}
dll(void) setCamera(const char* serializedData) {
	auto sh = DDD::ACamera::createFromSerialization(std::string(serializedData));
	if (cam != nullptr) {
		cam.reset();
		cam.swap(sh);
	}
	else
		cam = sh;
	cam->setScene(playground);
}
dll(void) initialize3d() {
	prepare3d();
}
dll(int) getSupportedClassesAt(int idx) {
	if (idx < 0)return -1;
	return supportedClasses[idx];
}
dll(int) getSupportedCamsAt(int idx) {
	if (idx < 0)return -1;
	return supportedCams[idx];
}
dll(void) startPreviewRender(int x, int y) {
	renderScene(x, y);
}

dll(BSTR) sceneFile() {
	return ANSItoBSTR(sceneOutputFile.c_str());
}
EXTERN_C_END
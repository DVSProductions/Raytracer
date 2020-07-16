#include <comutil.h>
#include "../3DTools/Raytracer.h"
#define dll(x) __declspec(dllexport) x __cdecl
EXTERN_C_START
//dll(void) BlastImage(void * ImageBuffer) {
//	Raytracer::BlastImage(ImageBuffer);
//}
double gameVersion = 1.0;
dll(double) GameVersion() {
	return gameVersion;
}
dll(void) BlastImage(uint8_t* ImageBuffer) {
	Raytracer::BlastImage(ImageBuffer);
}
dll(void) StartGameRender(int w, int h, double gamma) {
	Raytracer::turboRender(w, h, gamma);
}
dll(void) PrepareGameRender(int FSAA, int threads) {
	Raytracer::prepareTurboRender(FSAA, threads);
}
//dll(void) StartGameRender(int w, int h,int FSAA,double gamma,int threads) {
//	Raytracer::turboRender(w, h, FSAA,gamma,threads);
//}
dll(void) SetGameCamera(double angle, unsigned short reflections, const char* serialBG) {
	if (gameCam == nullptr) {
		gameCam = std::make_shared<DDD::GameCamera>(angle, DDD::Background(std::string(serialBG)), reflections);
	}
	gameCam->reload(angle,reflections,std::string(serialBG));
}
dll(void) MoveGameCamera(double x, double y, double z) {
	gameCam->moveCamera(x, y, z);
}
dll(void) RotateGameCamera(double x, double y, double z) {
	gameCam->rotateCamera(x, y, z);
}
EXTERN_C_END
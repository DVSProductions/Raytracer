#include "Resumability.h"
#include <comutil.h>
#define dll(x) __declspec(dllexport) x __cdecl
EXTERN_C_START
dll(bool) IsRestorable() {
	return checkResorabliity();
}
dll(void) Restore() {
	restoreRender();
}
dll(void) DiscardRestoreFiles() {
	deleteRestore();
}
dll(void) SetPause(bool value) {
	pauseRender(value);
}

EXTERN_C_END
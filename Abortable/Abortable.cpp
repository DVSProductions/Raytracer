#include "Abortable.h"
EXTERN_C_START
dll(void) Abort() {
	abortRender();
}
EXTERN_C_END
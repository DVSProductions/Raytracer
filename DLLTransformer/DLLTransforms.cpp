#include "DLLTransforms.h"
EXTERN_C_START
dll(int) GetSupportedTransformsAt(int idx) {
	if (idx < 0)return -1;
	return supportedTransforms[idx];
}
EXTERN_C_END
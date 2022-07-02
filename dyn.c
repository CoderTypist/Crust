#include <stdlib.h>
#include "dyn.h"
#include "str.h"

void* dyn_str(const char* pStr) {
    ASSERT_NOT_NULL(pStr, "pStr", "dyn_str");
    char* pHeap = (char*)calloc(1, STRLEN(pStr));
    ASSERT_CALLOC(pHeap, "pHead", "dyn_str");
    STRCPY(pHeap, pStr);
    return (void*)pHeap;
}

#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "dyn.h"
#include "str.h"

void* dyn_str(const char* pStr) {
    ASSERT_NOT_NULL(pStr, "pStr", "dyn_str");
    char* pHeap = (char*)calloc(1, STRLEN(pStr));
    ASSERT_CALLOC(pHeap, "pHead", "dyn_str");
    STRCPY(pHeap, pStr);
    return (void*)pHeap;
}

void* dyn_var(void* pVoid, int iSize) {
    ASSERT_NOT_NULL(pVoid, "pVoid", "dyn_var");
    void* pHeap = calloc(1, iSize);
    ASSERT_CALLOC(pHeap, "pHeap", "dyn_var");
    memcpy(pHeap, pVoid, iSize);
    return pHeap;
}

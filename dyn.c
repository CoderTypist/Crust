#include <stdio.h>
#include <stdlib.h>
#include "dyn.h"
#include "str.h"

void* dyn_str(const char* pStr) {
    return (void*)unsafe_strdup(pStr);
}

void* dyn_strn(const char* pStr, size_t n) {
    return safe_strndup(pStr, n);
}

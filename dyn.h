#ifndef _DYN_H_
#define _DYN_H_

#include <stdbool.h>
#include <string.h>
#include "assert.h"
#include "str.h"

void* dyn_str(const char* pStr);
void* dyn_var(void* pVoid, int iSize);

#define dyn(var)                                       \
    ({                                                 \
        void* pHeap = calloc(1, sizeof(typeof(var)) ); \
        ASSERT_CALLOC(pHeap, "pHeap", "dyn");          \
        typeof(var) copy = var;                        \
        memcpy(pHeap, &copy, sizeof(typeof(var)));     \
        pHeap;                                         \
    })

#define dyns(s) dyn_str(s)

#endif // _DYN_H_
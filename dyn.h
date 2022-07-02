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

#define unwrap(wrapper, type)                          \
( ( '*' == (#type)[STRLEN(#type)-1] )                  \
  ?                                                    \
  ({                                                   \
        type* pValue = wrapper->pValue;                \
        free(wrapper);                                 \
        pValue;                                        \
  })                                                   \
  :                                                    \
  ({                                                   \
        type value = *((type*)(wrapper->pValue));      \
        free(wrapper);                                 \
        value;                                         \
  })                                                   \
)

#define dyns(s) dyn_str(s)

#endif // _DYN_H_
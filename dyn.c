#include <stdio.h>
#include <stdlib.h>
#include "dyn.h"
#include "str.h"

void* dyn_str(const char* pStr) {

    ASSERT_NOT_NULL(pStr, "pStr", "dyn_str");

    size_t len = strnlen(pStr, MAX_LEN_STR);
    if( 0 == len ) {
        fprintf(stderr, "\tError: dyn_str(): pStr had len of 0\n");
        exit(-1);
    }

    if( '\0' != pStr[len] ) {
        fprintf(stderr, "\tError: dyn_str(): either...\n");
        fprintf(stderr, "\t\t- pStr is not NULL terminated\n");
        fprintf(stderr, "\t\t- length of pStr exceeds MAX_LEN_STR\n");
        exit(-1);
    }

    char* pHeap = (char*)calloc(1, len+1);
    ASSERT_CALLOC(pHeap, "pHead", "dyn_str");
    strncpy(pHeap, pStr, len); // calloc guarantees NULL termination
    return (void*)pHeap;
}

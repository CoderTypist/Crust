#include "assert.h"

void assert_malloc(void* pVoid, const char* strFunction) {
    if( NULL == pVoid ) {
        fprintf(stderr, "Error: %s(): malloc failed\n", strFunction);
        exit(-1);
    }
}
#include "assert.h"

void assert_malloc(void* pVoid, const char* strFunction) {
    if( NULL == pVoid ) {
        if( NULL == strFunction )
            fprintf(stderr, "Error: malloc failed\n");
        else
            fprintf(stderr, "Error: %s(): malloc failed\n", strFunction);
        exit(-1);
    }
}
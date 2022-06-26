#include "assert.h"
#include <stdio.h>
#include <stdlib.h>

void assert_alloc(void* pVoid, const char* strVar, const char* strFunction, const char* strAlloc) {
    if( !pVoid ) {
        if( strFunction ) {
            if( strVar ) {
                if( strAlloc )
                    fprintf(stderr, "Error: %s(): %s failed for %s\n", strFunction, strAlloc, strVar);
                else
                    fprintf(stderr, "Error: %s(): alloc failed for %s\n", strFunction, strVar);
            }
            else {
                if( strAlloc )
                    fprintf(stderr, "Error: %s(): %s failed\n", strFunction, strAlloc);
                else
                    fprintf(stderr, "Error: %s(): alloc failed\n", strFunction);
            }
        }
        else {
            if( strVar ) {
                if( strAlloc )
                    fprintf(stderr, "Error: %s failed for %s\n", strAlloc, strVar);
                else
                    fprintf(stderr, "Error: alloc failed for %s\n", strVar);
            }
            else {
                if( strAlloc )
                    fprintf(stderr, "Error: %s failed\n", strAlloc);
                else
                    fprintf(stderr, "Error: alloc failed\n");
            }
        }
        exit(-1);
    }
}

void assert_not_null(void* pVoid, const char* strVar, const char* strFunction) {
    if( !pVoid ) {
        if( strFunction ) {
            if( strVar )
                fprintf(stderr, "Error: %s(): expected non-null value, %s == NULL\n", strFunction, strVar);
            else
                fprintf(stderr, "Error: %s(): expected non-null value, received NULL\n", strFunction);
        }
        else {
            if( strVar ) 
                fprintf(stderr, "Error: expected non-null value, %s == NULL\n", strVar);
            else
                fprintf(stderr, "Error: expected non-null value, received NULL\n");
        }
    }
}

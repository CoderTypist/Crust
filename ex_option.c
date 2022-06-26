#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "option.h"

Option(int) is_positive(int);

int main() {
    
    Option(int) o = is_positive(4);

    if( is_some(o) ) {
        printf("%d is positive\n", (*(int*)(o->pValue)) );
    }

    return 0;
}

Option(int) is_positive(int x) {
    if( x > 0 ) {

        int* px = (int*)calloc(1, sizeof(int));
        ASSERT_CALLOC(px, "px", "main");
        *px = x;

        return Some(px);
    }
    else {
        return None;
    }
}
#include "option.h"
#include <stdio.h>

Option(int) is_positive(int);

int main() {
    
    int x = 4;
    Option(int) o = prime(x);

    if( is_some(o) ) {
        printf("%d is positive\n", (int)x);
    }

    void* p = NULL;
    Option opt = p;
    return 0;
}

Option(int) is_positive(int x) {
    if( x > 0 ) {
        return Some(x);
    }
    else {
        return None;
    }
}
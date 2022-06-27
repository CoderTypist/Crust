#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dyn.h"
#include "option.h"

// NOTE: Examples do not yet free memory

void example_01();
Option(int) is_positive(int);
void example_02();
Option(char*) is_capital(const char* word);

int main() {
    
    printf("EXAMPLE 01:\n");
    example_01();
    printf("\n");

    printf("EXAMPLE 02:\n");
    example_02();
    printf("\n");

    return 0;
}

void example_01() {

    Option(int) o = is_positive(4);

    if( is_some(o) ) {
        printf("\t%d is positive\n", (*(int*)(o->pValue)) );
    }
}

Option(int) is_positive(int x) {
    if( x > 0 ) {
        return Some(dyn(x));
    }
    else {
        return None;
    }
}

void example_02() {
    char words[4][10] = {
        "apple",
        "Apple",
        "orange",
        "ORANGE"
    };

    Option(char*) o1 = is_capital(words[0]);
    if( is_some(o1) ) {
        printf("\t%s starts with a capital letter\n", (char*)(o1->pValue));
    }

    Option(char*) o2 = is_capital(words[1]);
    if( is_some(o2) ) {
        printf("\t%s starts with a capital letter\n", (char*)(o2->pValue));
    }

    Option(char*) o3 = is_capital(words[2]);
    if( is_some(o3) ) {
        printf("\t%s starts with a capital letter\n", (char*)(o3->pValue));
    }

    Option(char*) o4 = is_capital(words[3]);
    if( is_some(o4) ) {
        printf("\t%s starts with a capital letter\n", (char*)(o4->pValue));
    }
}

Option(char*) is_capital(const char* word) {
    if( NULL == word )
        return None;
    if( word[0] >= 'A' && word[0] <= 'Z' ) { 
        return Some(dyn_str(word));
    }
    return None;
}

#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dyn.h"
#include "wrapper.h"

// NOTE: Examples do not yet free memory

void example_01();
Option(int) is_positive_o(int);

Result(bool, char*) is_positive_r(int x);
void example_02();
Option(char*) is_capital_o(const char* word);

void example_03();
Result(bool, char*) is_positive_r(int x);

void example_04();
Result(bool, char*) is_capital_r(const char* word);

int main() {
    
    printf("EXAMPLE 01:\n");
    example_01();
    printf("\n");

    printf("EXAMPLE 02:\n");
    example_02();
    printf("\n");

    printf("EXAMPLE 03:\n");
    example_03();
    printf("\n");

    printf("EXAMPLE 04:\n");
    example_04();
    printf("\n");

    return 0;
}

/********************************************************************************************/

void example_01() {

    Option(int) o = is_positive_o(4);

    // printf("\t%d is positive\n", (*(int*)(o->pValue)) );
    if( is_some(o) ) {
        printf("\t%d is positive\n", unwrap(o, int) );
    }
}

Option(int) is_positive_o(int x) {
    if( x > 0 ) {
        return Some(dyn(x));
    }
    else {
        return None;
    }
}

/********************************************************************************************/

void example_02() {
    char words[4][10] = {
        "apple",
        "Apple",
        "orange",
        "ORANGE"
    };

    Option(char*) o1 = is_capital_o(words[0]);
    if( is_some(o1) ) {
        printf("\t%s starts with a capital letter\n", unwrap(o1, char*));
    }

    Option(char*) o2 = is_capital_o(words[1]);
    if( is_some(o2) ) {
        printf("\t%s starts with a capital letter\n", unwrap(o2, char*));
    }

    Option(char*) o3 = is_capital_o(words[2]);
    if( is_some(o3) ) {
        printf("\t%s starts with a capital letter\n", unwrap(o3, char*));
    }

    Option(char*) o4 = is_capital_o(words[3]);
    if( is_some(o4) ) {
        printf("\t%s starts with a capital letter\n", unwrap(o4, char*));
    }
}

Option(char*) is_capital_o(const char* word) {
    if( NULL == word )
        return None;
    if( word[0] >= 'A' && word[0] <= 'Z' ) { 
        return Some(dyns(word));
    }
    return None;
}

/********************************************************************************************/

void example_03() {

    Result(bool, char*) r = is_positive_r(4);
    
    if( is_ok(r) )
        printf("\t%d is positive\n", (*(int*)(r->pValue)) );
    else
        printf("\tError: %s\n", (char*)(r->pValue));
}

Result(bool, char*) is_positive_r(int x) {
    if( 0 == x )
        return Err(dyns("Can't tell if 0 is positive or negative"));
    else if( x > 0 )
        return Ok(dyn(true));
    else
        return Ok(dyn(false));
}

/********************************************************************************************/

void example_04() {
    char words[4][10] = {
        "apple",
        "Apple",
        "orange",
        "ORANGE"
    };

    Result(char*, char*) r1 = is_capital_r(words[0]);
    if( is_ok(r1) )
        printf("\t%s starts with a capital letter\n", unwrap(r1, char*));
    else
        printf("\tError: %s\n", unwrap(r1, char*));

    Result(char*, char*) r2 = is_capital_r(words[1]);
    if( is_ok(r2) )
        printf("\t%s starts with a capital letter\n", unwrap(r2, char*));
    else
        printf("\tError: %s\n", unwrap(r2, char*));

    Result(char*, char*) r3 = is_capital_r(words[2]);
    if( is_ok(r3) )
        printf("\t%s starts with a capital letter\n", unwrap(r3, char*));
    else
        printf("\tError: %s\n", unwrap(r3, char*));

    Result(char*, char*) r4 = is_capital_r(words[3]);
    if( is_ok(r4) )
        printf("\t%s starts with a capital letter\n", unwrap(r4, char*));
    else
        printf("\tError: %s\n", unwrap(r4, char*));
}

Result(char*, char*) is_capital_r(const char* word) {
    if( NULL == word )
        return Err(dyns("Received NULL"));
    if( word[0] >= 'A' && word[0] <= 'Z' ) { 
        return Ok(dyns(word));
    }
    return Err(dyns("First character was not a capital letter"));
}

/********************************************************************************************/


/********************************************************************************************/

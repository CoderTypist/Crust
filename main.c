#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dyn.h"
#include "wrapper.h"

// TODO: Tests for try_ok() and try_some()

Option(int) is_positive_o(int x);
Result(bool, char*) is_positive_r(int x);

void test_is_some();
void test_is_none();
void test_is_ok();
void test_is_err();

void test_if_some();
void test_if_none();
void test_if_ok();
void test_if_err();

Option(int) is_positive_intermediary_try_o(int x);
Result(bool, char*) is_positive_intermediary_try_r(int x);

void test_try_with_option_some();
void test_try_with_option_none();
void test_try_with_result_ok();
void test_try_with_result_err();

void test_try_some_with_option_some();
void test_try_some_with_option_none();
void test_try_some_with_result_ok();
void test_try_some_with_result_err();

void test_try_ok_with_option_some();
void test_try_ok_with_option_none();
void test_try_ok_with_result_ok();
void test_try_ok_with_result_err();

int main() {

    test_is_some();
    test_is_none();
    test_is_ok();
    test_is_err();

    test_if_some();
    test_if_none();
    test_if_ok();
    test_if_err();

    test_try_with_option_some();
    test_try_with_option_none();
    test_try_with_result_ok();
    test_try_with_result_err();

    test_try_some_with_option_some();
    test_try_some_with_option_none();
    test_try_some_with_result_ok();
    test_try_some_with_result_err();

    test_try_ok_with_option_some();
    test_try_ok_with_option_none();
    test_try_ok_with_result_ok();
    test_try_ok_with_result_err();

    /*
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
    */

    return 0;
}

Option(int) is_positive_o(int x) {
    if( x > 0 ) {
        return Some(dyn(x));
    }
    else {
        return None;
    }
}

Result(bool, char*) is_positive_r(int x) {
    if( 0 == x )
        return Err(dyns("Can't tell if 0 is positive or negative"));
    else if( x > 0 )
        return Ok(dyn(true));
    else
        return Err(dyns("Value is negative"));
}

void test_is_some() {
    Option(int) o = is_positive_o(1);
    if( is_some(o) )
        printf("\tPASS: test_is_some(): o: Received Some: %d\n", unwrap(o, int));
    else
        printf("\nFAIL: test_is_some(): o: Received None, expected Some\n");
}

void test_is_none() {
    Option(int) o = is_positive_o(-1);
    if( is_none(o) )
        printf("\tPASS: test_is_none(): o: Received None\n");
    else
        printf("\nFAIL: test_is_none(): o: Received Some, expected None\n");
}

void test_is_ok() {
    Result(bool, char*) r = is_positive_r(1);
    if( is_ok(r) )
        printf("\tPASS: test_is_ok(): r: Received Ok: %d\n", unwrap(r, bool));
    else
        printf("\nFAIL: test_is_ok(): r: Received Err, expected Ok\n");
}

void test_is_err() {
    Result(bool, char*) r = is_positive_r(-1);
    if( is_err(r) )
        printf("\tPASS: test_is_err(): r: Received Err\n");
    else
        printf("\nFAIL: test_is_err(): r: Received Ok, expected Err\n");
}

void test_if_some() {
    int i = if_some(is_positive_o(1), int);
    printf("\tPASS: test_if_some(): o: Received Some: %d\n", i);
    // int i = if_some(is_positive_o(-1), int);
    // Error: if_some(): expected WRAPPER_SOME, ecountered WRAPPER_NONE
}

void test_if_none() {
    int i = if_none(is_positive_o(-1), int);
    printf("\tPASS: test_if_none(): o: Received None\n");
    // int i = if_none(is_positive_o(1), int);
    // Error: if_none(): expected WRAPPER_NONE, ecountered WRAPPER_SOME
}

void test_if_ok() {
    bool b = if_ok(is_positive_r(1), bool);
    printf("\tPASS: test_if_ok(): r: Received Ok: %d\n", b);
    // bool b = if_ok(is_positive_r(-1), bool);
    // Error: if_ok(): expected WRAPPER_OK, ecountered WRAPPER_ERR
}

void test_if_err() {
    char* s = if_err(is_positive_r(-1), char*);
    printf("\tPASS: test_if_err(): r: Received Err: %s\n", s);
    // char* s = if_err(is_positive_r(1), bool);
    // Error: if_err(): expected WRAPPER_ERR, ecountered WRAPPER_OK
}

Option(int) is_positive_intermediary_try_o(int x) {
    int i = try(is_positive_o(x), int);
    printf("\t\tis_positive_intermediary_try_o(): i: Received Some: %d\n", i);
    return Some(dyn(i));
}

Result(bool, char*) is_positive_intermediary_try_r(int x) {
    bool b = try(is_positive_r(x), bool);
    printf("\t\tis_positive_intermediary_try_r(): b: Received Ok: %d\n", b);
    return Ok(dyn(b));
}

void test_try_with_option_some() {
    Option(int) o = is_positive_intermediary_try_o(1);
    if( is_some(o) )
        printf("\tPASS: test_try_with_option_some(): o: Received Some: %d\n", unwrap(o, int));
    else
        printf("\nFAIL: test_try_with_option_some(): o: Received None, expected Some\n");
}

void test_try_with_option_none() {
    Option(int) o = is_positive_intermediary_try_o(-1);
    if( is_none(o) )
        printf("\tPASS: test_try_with_option_none(): o: Received None\n");
    else
        printf("\nFAIL: test_try_with_option_none(): o: Received Some, expected None\n");
}

void test_try_with_result_ok() {
    Result(bool, char*) r = is_positive_intermediary_try_r(1);
    if( is_ok(r) )
        printf("\tPASS: test_try_with_result_ok(): r: Received Ok: %d\n", unwrap(r, bool));
    else
        printf("\nFAIL: test_try_with_result_ok(): r: Received Err, expected Ok\n");
}

void test_try_with_result_err() {
    Result(bool, char*) r = is_positive_intermediary_try_r(-1);
    if( is_err(r) )
        printf("\tPASS: test_try_with_result_err(): r: Received Err\n");
    else
        printf("\nFAIL: test_try_with_result_err(): r: Received Ok, expected Err\n");
}

void test_try_some_with_option_some() {

}

void test_try_some_with_option_none() {

}

void test_try_some_with_result_ok() {

}

void test_try_some_with_result_err() {

}

void test_try_ok_with_option_some() {

}

void test_try_ok_with_option_none() {

}

void test_try_ok_with_result_ok() {

}

void test_try_ok_with_result_err() {

}

/*

void example_01();
Option(int) is_positive_o(int);

Result(bool, char*) is_positive_r(int x);
void example_02();
Option(char*) is_capital_o(const char* word);

void example_03();
Result(bool, char*) is_positive_r(int x);

void example_04();
Result(char*, char*) is_capital_r(const char* word);

/////////////////////////////////////////////////////////////////////////////////////////////

void example_01() {

    Option(int) o = is_positive_o(4);

    // printf("\t%d is positive\n", (*(int*)(o->pValue)) );
    if( is_some(o) ) {
        printf("\t%d is positive\n", unwrap(o, int) );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////

void example_03() {

    Result(bool, char*) r = is_positive_r(4);
    
    if( is_ok(r) )
        printf("\t%d is positive\n", (*(int*)(r->pValue)) );
    else
        printf("\tError: %s\n", (char*)(r->pValue));
}

/////////////////////////////////////////////////////////////////////////////////////////////

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
    // else
    //     printf("\tError: %s\n", unwrap(r1, char*));

    Result(char*, char*) r2 = is_capital_r(words[1]);
    if( is_ok(r2) )
        printf("\t%s starts with a capital letter\n", unwrap(r2, char*));
    // else
    //     printf("\tError: %s\n", unwrap(r2, char*));

    Result(char*, char*) r3 = is_capital_r(words[2]);

    if( is_ok(r3) )
        printf("\t%s starts with a capital letter\n", unwrap(r3, char*));
    // else
    //     printf("\tError: %s\n", unwrap(r3, char*));

    Result(char*, char*) r4 = is_capital_r(words[3]);
    if( is_ok(r4) )
        printf("\t%s starts with a capital letter\n", unwrap(r4, char*));
    // else
    //     printf("\tError: %s\n", unwrap(r4, char*));
}

Result(char*, char*) is_capital_r(const char* word) {
    if( NULL == word )
        return Err(dyns("Received NULL"));
    if( word[0] >= 'A' && word[0] <= 'Z' ) { 
        return Ok(dyns(word));
    }
    return Err(dyns("First character was not a capital letter"));
}

/////////////////////////////////////////////////////////////////////////////////////////////
*/
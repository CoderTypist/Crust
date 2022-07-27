#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "dyn.h"
#include "wrapper.h"

/*********************************************************************************************/

Option(int) is_positive_o(int x);
Result(bool, char*) is_positive_r(int x);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_is_some();
void test_is_none();
void test_is_ok();
void test_is_err();

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_if_some();
void test_if_none();
void test_if_ok();
void test_if_err();

/*********************************************************************************************/

Option(int) is_positive_intermediary_try_o(int x);
Result(bool, char*) is_positive_intermediary_try_r(int x);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_try_with_option_some();
void test_try_with_option_none();
void test_try_with_result_ok();
void test_try_with_result_err();

/*********************************************************************************************/

Option(int) is_positive_intermediary_try_some_o(int x);
Result(bool, char*) is_positive_intermediary_try_ok_r(int x);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_try_some_with_option_some();
void test_try_some_with_option_none();

void test_try_ok_with_result_ok();
void test_try_ok_with_result_err();

/*********************************************************************************************/


int main() {

    printf("\n");
    printf("\tTESTS: is_<...>():\n");
    test_is_some();
    test_is_none();
    test_is_ok();
    test_is_err();
    printf("\n");

    printf("\tTESTS: if_<...>():\n");
    test_if_some();
    test_if_none();
    test_if_ok();
    test_if_err();
    printf("\n");

    printf("\tTESTS: try():\n");
    test_try_with_option_some();
    test_try_with_option_none();
    test_try_with_result_ok();
    test_try_with_result_err();
    printf("\n");

    printf("\tTESTS: try_some():\n");
    test_try_some_with_option_some();
    test_try_some_with_option_none();
    printf("\n");

    printf("\tTESTS: try_ok():\n");
    test_try_ok_with_result_ok();
    test_try_ok_with_result_err();
    printf("\n");

    return 0;
}

/*********************************************************************************************/

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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_is_some() {
    Option(int) o = is_positive_o(1);
    if( is_some(o) )
        printf("\t\tPASS: test_is_some(): o: Received Some: %d\n", unwrap(o, int));
    else
        printf("\t\tFAIL: test_is_some(): o: Received None, expected Some\n");
}

void test_is_none() {
    Option(int) o = is_positive_o(-1);
    if( is_none(o) )
        printf("\t\tPASS: test_is_none(): o: Received None\n");
    else
        printf("\t\tFAIL: test_is_none(): o: Received Some, expected None\n");
}

void test_is_ok() {
    Result(bool, char*) r = is_positive_r(1);
    if( is_ok(r) )
        printf("\t\tPASS: test_is_ok(): r: Received Ok: %d\n", unwrap(r, bool));
    else
        printf("\t\tFAIL: test_is_ok(): r: Received Err, expected Ok\n");
}

void test_is_err() {
    Result(bool, char*) r = is_positive_r(-1);
    if( is_err(r) )
        printf("\t\tPASS: test_is_err(): r: Received Err\n");
    else
        printf("\t\tFAIL: test_is_err(): r: Received Ok, expected Err\n");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_if_some() {
    int i = if_some(is_positive_o(1), int);
    printf("\t\tPASS: test_if_some(): o: Received Some: %d\n", i);
    // int i = if_some(is_positive_o(-1), int);
    // Error: if_some(): expected WRAPPER_SOME, ecountered WRAPPER_NONE
}

void test_if_none() {
    int i = if_none(is_positive_o(-1), int);
    printf("\t\tPASS: test_if_none(): o: Received None\n");
    // int i = if_none(is_positive_o(1), int);
    // Error: if_none(): expected WRAPPER_NONE, ecountered WRAPPER_SOME
}

void test_if_ok() {
    bool b = if_ok(is_positive_r(1), bool);
    printf("\t\tPASS: test_if_ok(): r: Received Ok: %d\n", b);
    // bool b = if_ok(is_positive_r(-1), bool);
    // Error: if_ok(): expected WRAPPER_OK, ecountered WRAPPER_ERR
}

void test_if_err() {
    char* s = if_err(is_positive_r(-1), char*);
    printf("\t\tPASS: test_if_err(): r: Received Err: %s\n", s);
    // char* s = if_err(is_positive_r(1), bool);
    // Error: if_err(): expected WRAPPER_ERR, ecountered WRAPPER_OK
}

/*********************************************************************************************/

Option(int) is_positive_intermediary_try_o(int x) {
    int i = try(is_positive_o(x), int);
    printf("\t\t- is_positive_intermediary_try_o(): i: Received Some: %d\n", i);
    return Some(dyn(i));
}

Result(bool, char*) is_positive_intermediary_try_r(int x) {
    bool b = try(is_positive_r(x), bool);
    printf("\t\t- is_positive_intermediary_try_r(): b: Received Ok: %d\n", b);
    return Ok(dyn(b));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_try_with_option_some() {
    Option(int) o = is_positive_intermediary_try_o(1);
    if( is_some(o) )
        printf("\t\tPASS: test_try_with_option_some(): o: Received Some: %d\n", unwrap(o, int));
    else
        printf("\t\tFAIL: test_try_with_option_some(): o: Received None, expected Some\n");
}

void test_try_with_option_none() {
    Option(int) o = is_positive_intermediary_try_o(-1);
    if( is_none(o) )
        printf("\t\tPASS: test_try_with_option_none(): o: Received None\n");
    else
        printf("\t\tFAIL: test_try_with_option_none(): o: Received Some, expected None\n");
}

void test_try_with_result_ok() {
    Result(bool, char*) r = is_positive_intermediary_try_r(1);
    if( is_ok(r) )
        printf("\t\tPASS: test_try_with_result_ok(): r: Received Ok: %d\n", unwrap(r, bool));
    else
        printf("\t\tFAIL: test_try_with_result_ok(): r: Received Err, expected Ok\n");
}

void test_try_with_result_err() {
    Result(bool, char*) r = is_positive_intermediary_try_r(-1);
    if( is_err(r) )
        printf("\t\tPASS: test_try_with_result_err(): r: Received Err\n");
    else
        printf("\t\tFAIL: test_try_with_result_err(): r: Received Ok, expected Err\n");
}

/*********************************************************************************************/

Option(int) is_positive_intermediary_try_some_o(int x) {
    int i = try_some(is_positive_o(x), int);
    printf("\t\t- is_positive_intermediary_try_some_o(): i: Received Some: %d\n", i);
    return Some(dyn(i));
}

Result(bool, char*) is_positive_intermediary_try_ok_r(int x) {
    bool b = try_ok(is_positive_r(x), bool);
    printf("\t\t- is_positive_intermediary_try_ok_r(): b: Received Ok: %d\n", b);
    return Ok(dyn(b));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void test_try_some_with_option_some() {
    Option(int) o = is_positive_intermediary_try_some_o(1);
    if( is_some(o) )
        printf("\t\tPASS: test_try_some_with_option_some(): o: Received Some: %d\n", unwrap(o, int));
    else
        printf("\t\tFAIL: test_try_some_with_option_some(): o: Received None, expected Some\n");
}

void test_try_some_with_option_none() {
    Option(int) o = is_positive_intermediary_try_some_o(-1);
    if( is_none(o) )
        printf("\t\tPASS: test_try_some_with_option_none(): o: Received None\n");
    else
        printf("\t\tFAIL: test_try_some_with_option_none(): o: Received Some, expected None\n");
}

void test_try_ok_with_result_ok() {
    Result(bool, char*) r = is_positive_intermediary_try_ok_r(1);
    if( is_ok(r) )
        printf("\t\tPASS: test_try_ok_with_result_ok(): r: Received Ok: %d\n", unwrap(r, bool));
    else
        printf("\t\tFAIL: test_try_ok_with_result_ok(): r: Received Err, expected Ok\n");
}

void test_try_ok_with_result_err() {
    Result(bool, char*) r = is_positive_intermediary_try_ok_r(-1);
    if( is_err(r) )
        printf("\t\tPASS: test_try_ok_with_result_err(): r: Received Err\n");
    else
        printf("\t\tFAIL: test_try_ok_with_result_err(): r: Received Ok, expected Err\n");    
}
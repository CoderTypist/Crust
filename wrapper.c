#include <stdlib.h>
#include "wrapper.h"

bool _is_option(Wrapper_t* pWrapper) {
    ASSERT_NOT_NULL(pWrapper, "pWrapper", "_is_option");
    if( WRAPPER_SOME == pWrapper->type || WRAPPER_NONE == pWrapper->type )
        return true;
    return false;
}

bool _is_result(Wrapper_t* pWrapper) {
    ASSERT_NOT_NULL(pWrapper, "pWrapper", "_is_result");
    if( WRAPPER_OK == pWrapper->type || WRAPPER_ERR == pWrapper->type )
        return true;
    return false;
}

static Option_t* Option_new() {
    Option_t* pNew = (Option_t*)calloc(1, sizeof(Option_t));
    ASSERT_CALLOC(pNew, "pNew", "Option_new");
    return pNew;
}

Option_t* Option_Some(void* pValue) {
    Option_t* pOption = Option_new();
    pOption->type = WRAPPER_SOME;
    pOption->pValue = pValue;
    return pOption;
}

Option_t* Option_None() {
    Option_t* pOption = Option_new();
    pOption->type = WRAPPER_NONE;
    return pOption;
}

bool is_some(Option_t* pOption) {
    ASSERT_NOT_NULL(pOption, "pOption", "is_some");
    return WRAPPER_SOME == pOption->type;
}

bool is_none(Option_t* pOption) {
    ASSERT_NOT_NULL(pOption, "pOption", "is_none");
    return WRAPPER_NONE == pOption->type;
}

static Result_t* Result_new() {
    Result_t* pNew = (Result_t*)calloc(1, sizeof(Result_t));
    ASSERT_CALLOC(pNew, "pNew", "Result_new");
    return pNew;
}

Result_t* Result_Ok(void* pValue) {
    Result_t* pResult = Result_new();
    pResult->type = WRAPPER_OK;
    pResult->pValue = pValue;
    return pResult;
}

Result_t* Result_Err(void *pValue) {
    Result_t* pResult = Result_new();
    pResult->type = WRAPPER_ERR;
    pResult->pValue = pValue;
    return pResult;
}

bool is_ok(Result_t* pResult) {
    ASSERT_NOT_NULL(pResult, "pResult", "is_some");
    return WRAPPER_OK == pResult->type;
}

bool is_err(Result_t* pResult) {
    ASSERT_NOT_NULL(pResult, "pResult", "is_none");
    return WRAPPER_ERR == pResult->type;
}
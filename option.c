#include <stdlib.h>
#include "assert.h"
#include "option.h"

static Option_t* Option_new() {
    Option_t* pNew = (Option_t*)calloc(1, sizeof(Option_t));
    ASSERT_CALLOC(pNew, "pNew", "Option_new");
    return pNew;
}

Option_t* Option_Some(void* pValue) {
    Option_t* pOption = Option_new();
    pOption->option = OPTION_SOME;
    pOption->pValue = pValue;
    return pOption;
}

Option_t* Option_None() {
    Option_t* pOption = Option_new();
    pOption->option = OPTION_NONE;
    return pOption;
}

bool is_some(Option_t* pOption) {
    ASSERT_NOT_NULL(pOption, "pOption", "is_some");
    return OPTION_SOME == pOption->option;
}

bool is_none(Option_t* pOption) {
    ASSERT_NOT_NULL(pOption, "pOption", "is_none");
    return OPTION_NONE == pOption->option;
}

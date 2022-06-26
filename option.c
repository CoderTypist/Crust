#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"
#include "option.h"

bool is_some(Option_t pOption) {
    return NULL != pOption;
}

bool is_none(Option_t pOption) {
    return NULL == pOption;
}

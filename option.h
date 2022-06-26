#ifndef _OPTION_H_
#define _OPTION_H_

#include <stdbool.h>

enum Option_e {
    OPTION_SOME,
    OPTION_NONE
};

typedef struct Option_t {
    enum Option_e option;
    void* pValue;
} Option_t;

Option_t* Option_Some(void* pValue);
Option_t* Option_None();
bool is_some(Option_t* pOption);
bool is_none(Option_t* pOption);

#define Option(annot) Option_t*
#define Some(p) Option_Some((void*)p)
#define None Option_None()

#endif // _OPTION_H_
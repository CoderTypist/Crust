#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"

enum Wrapper_e {
    WRAPPER_SOME,
    WRAPPER_NONE,
    WRAPPER_OK,
    WRAPPER_ERR
};

typedef struct Wrapper_t {
    enum Wrapper_e type;
    void* pValue;
} Wrapper_t;

typedef Wrapper_t Option_t;
typedef Wrapper_t Result_t;

bool _is_option(Wrapper_t* pWrapper);
bool _is_result(Wrapper_t* pWrapper);

Option_t* Option_Some(void* pValue);
Option_t* Option_None();
bool is_some(Option_t* pOption);
bool is_none(Option_t* pOption);

Result_t* Result_Ok(void* pValue);
Result_t* Result_Err(void *pValue);
bool is_ok(Result_t* pResult);
bool is_err(Result_t* pResult);

#define Wrapper Wrapper_t*
#define Option(T) Option_t*
#define Result(T, E) Result_t*
#define Some(p) Option_Some((void*)p)
#define None Option_None()
#define Ok(p) Result_Ok((void*)p)
#define Err(p) Result_Err((void*)p)

#define _unwrap_raw(wrapper, utype)                      \
( ( '*' == (#utype)[STRLEN(#utype)-1] )                  \
  ?                                                      \
  ({                                                     \
        utype* pValue = wrapper->pValue;                 \
        free(wrapper);                                   \
        pValue;                                          \
  })                                                     \
  :                                                      \
  ({                                                     \
        utype value = *((utype*)(wrapper->pValue));      \
        free(wrapper);                                   \
        value;                                           \
  })                                                     \
)

#define unwrap(wrapper, utype)                                                            \
({                                                                                       \
    ASSERT_NOT_NULL(wrapper, "wrapper", "unwrap");                                       \
    if( !is_some(wrapper) && !is_ok(wrapper) ) {                                         \
        fprintf(stderr, "Error: unwrap(): expected WRAPPER_SOME or WRAPPER_OK\n");       \
        switch(wrapper->type) {                                                          \
            case WRAPPER_NONE:                                                           \
                fprintf(stderr, "\tencounted WRAPPER_NONE\n");                           \
                break;                                                                   \
            case WRAPPER_ERR:                                                            \
                fprintf(stderr, "\tencountered WRAPPER_ERR\n");                          \
                break;                                                                   \
            default:                                                                     \
                fprintf(stderr, "\tinvalid wrapper type\n");                             \
        }                                                                                \
        exit(-1);                                                                        \
    }                                                                                    \
    _unwrap_raw(wrapper, utype);                                                          \
})

#endif // _WRAPPER_H_
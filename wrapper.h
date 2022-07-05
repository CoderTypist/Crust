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

#define _unwrap_raw(wrapper, utype)                     \
    ( ( '*' == (#utype)[STRLEN(#utype)-1] )             \
      ?                                                 \
      ({                                                \
            utype* pValue = wrapper->pValue;            \
            free(wrapper);                              \
            pValue;                                     \
      })                                                \
      :                                                 \
      ({                                                \
            utype value = *((utype*)(wrapper->pValue)); \
            free(wrapper);                              \
            value;                                      \
      })                                                \
    )

// WRAPPER_SOME: _unwrap_raw(wrapper, utype)
// WRAPPER_NONE: exit(-1)
// WRAPPER_OK:   _unwrap_raw(wrapper, utype)
// WRAPPER_ERR:  exit(-1)
#define unwrap(wrapper, utype)                                                                    \
    ({                                                                                            \
        ASSERT_NOT_NULL(wrapper, "wrapper", "unwrap");                                            \
        if( ( WRAPPER_SOME != wrapper->type ) && ( WRAPPER_OK != wrapper->type ) ) {              \
            fprintf(stderr, "Error: unwrap(): expected WRAPPER_SOME or WRAPPER_OK, ecountered "); \
            switch(wrapper->type) {                                                               \
                case WRAPPER_NONE:                                                                \
                    fprintf(stderr, "WRAPPER_NONE\n");                                            \
                    break;                                                                        \
                case WRAPPER_ERR:                                                                 \
                    fprintf(stderr, "WRAPPER_ERR\n");                                             \
                    break;                                                                        \
                default:                                                                          \
                    fprintf(stderr, "invalid wrapper type\n");                                    \
            }                                                                                     \
            BLAZE;                                                                                \
            exit(-1);                                                                             \
        }                                                                                         \
        _unwrap_raw(wrapper, utype);                                                              \
    })

// WRAPPER_SOME: _unwrap_raw(wrapper, utype)
// WRAPPER_NONE: exit(-1)
// WRAPPER_OK:   exit(-1)
// WRAPPER_ERR:  exit(-1)
#define if_some(wrapper, utype)                                                      \
    ({                                                                               \
        ASSERT_NOT_NULL(wrapper, "wrapper", "if_some");                              \
        if( WRAPPER_SOME != wrapper->type ) {                                        \
            fprintf(stderr, "Error: if_some(): expected WRAPPER_SOME, ecountered "); \
            switch(wrapper->type) {                                                  \
                case WRAPPER_NONE:                                                   \
                    fprintf(stderr, "WRAPPER_NONE\n");                               \
                    break;                                                           \
                case WRAPPER_OK:                                                     \
                    fprintf(stderr, "WRAPPER_OK\n");                                 \
                    break;                                                           \
                case WRAPPER_ERR:                                                    \
                    fprintf(stderr, "WRAPPER_ERR\n");                                \
                    break;                                                           \
                default:                                                             \
                    fprintf(stderr, "invalid wrapper type\n");                       \
            }                                                                        \
            BLAZE;                                                                   \
            exit(-1);                                                                \
        }                                                                            \
        _unwrap_raw(wrapper, utype);                                                 \
    })

// WRAPPER_SOME: exit(-1)
// WRAPPER_NONE: NULL
// WRAPPER_OK:   exit(-1)
// WRAPPER_ERR:  exit(-1)
#define if_none(wrapper, utype)                                                      \
    ({                                                                               \
        ASSERT_NOT_NULL(wrapper, "wrapper", "if_none");                              \
        if( WRAPPER_NONE != wrapper->type ) {                                        \
            fprintf(stderr, "Error: if_none(): expected WRAPPER_NONE, ecountered "); \
            switch(wrapper->type) {                                                  \
                case WRAPPER_SOME:                                                   \
                    fprintf(stderr, "WRAPPER_SOME\n");                               \
                    break;                                                           \
                case WRAPPER_OK:                                                     \
                    fprintf(stderr, "WRAPPER_OK\n");                                 \
                    break;                                                           \
                case WRAPPER_ERR:                                                    \
                    fprintf(stderr, "WRAPPER_ERR\n");                                \
                    break;                                                           \
                default:                                                             \
                    fprintf(stderr, "invalid wrapper type\n");                       \
            }                                                                        \
            BLAZE;                                                                   \
            exit(-1);                                                                \
        }                                                                            \
        free(wrapper);                                                               \
        NULL;                                                                        \
    })

// WRAPPER_SOME: exit(-1)
// WRAPPER_NONE: exit(-1)
// WRAPPER_OK:   _unwrap_raw(wrapper, utype)
// WRAPPER_ERR:  exit(-1)
#define if_ok(wrapper, utype)                                                    \
    ({                                                                           \
        ASSERT_NOT_NULL(wrapper, "wrapper", "if_ok");                            \
        if( WRAPPER_OK != wrapper->type ) {                                      \
            fprintf(stderr, "Error: if_ok(): expected WRAPPER_OK, ecountered "); \
            switch(wrapper->type) {                                              \
                case WRAPPER_SOME:                                               \
                    fprintf(stderr, "WRAPPER_SOME\n");                           \
                    break;                                                       \
                case WRAPPER_NONE:                                               \
                    fprintf(stderr, "WRAPPER_NONE\n");                           \
                    break;                                                       \
                case WRAPPER_ERR:                                                \
                    fprintf(stderr, "WRAPPER_ERR\n");                            \
                    break;                                                       \
                default:                                                         \
                    fprintf(stderr, "invalid wrapper type\n");                   \
            }                                                                    \
            BLAZE;                                                               \
            exit(-1);                                                            \
        }                                                                        \
        _unwrap_raw(wrapper, utype);                                             \
    })

// WRAPPER_SOME: exit(-1)
// WRAPPER_NONE: exit(-1)
// WRAPPER_OK:   exit(-1)
// WRAPPER_ERR:  _unwrap_raw(wrapper, utype)
#define if_err(wrapper, utype)                                                 \
({                                                                             \
    ASSERT_NOT_NULL(wrapper, "wrapper", "if_err");                             \
    if( WRAPPER_ERR != wrapper->type ) {                                       \
        fprintf(stderr, "Error: if_err(): expected WRAPPER_ERR, ecountered "); \
        switch(wrapper->type) {                                                \
            case WRAPPER_SOME:                                                 \
                fprintf(stderr, "WRAPPER_SOME\n");                             \
                break;                                                         \
            case WRAPPER_NONE:                                                 \
                fprintf(stderr, "WRAPPER_NONE\n");                             \
                break;                                                         \
            case WRAPPER_OK:                                                   \
                fprintf(stderr, " WRAPPER_OK\n");                    \
                break;                                                         \
            default:                                                           \
                fprintf(stderr, " invalid wrapper type\n");                    \
        }                                                                      \
        BLAZE;                                                                 \
        exit(-1);                                                              \
    }                                                                          \
    _unwrap_raw(wrapper, utype);                                               \
})

// WRAPPER_SOME: _unwrap_raw(wrapper, utype)
// WRAPPER_NONE: wrapper
// WRAPPER_OK:   _unwrap_raw(wrapper, utype)
// WRAPPER_ERR:  wrapper
#define try(wrapper, utype)                                                      \
    ({                                                                               \
        ASSERT_NOT_NULL(wrapper, "wrapper", "try");                                  \
        if( ( WRAPPER_SOME != wrapper->type ) && ( WRAPPER_OK != wrapper->type ) ) { \
            switch(wrapper->type) {                                                  \
                case WRAPPER_NONE:                                                   \
                case WRAPPER_ERR:                                                    \
                    return _unwrap_raw(wrapper, utype);                              \
                default:                                                             \
                    fprintf(stderr, "Error: try(): invalid wrapper type\n");         \
                    BLAZE;                                                           \
                    exit(-1);                                                        \
            }                                                                        \
        }                                                                            \
        _unwrap_raw(wrapper, utype);                                                 \
    })

// WRAPPER_SOME: _unwrap_raw(wrapper, utype)
// WRAPPER_NONE: wrapper
// WRAPPER_OK:   exit(-1)
// WRAPPER_ERR:  exit(-1)
#define try_some(wrapper, utype)                                                                           \
    ({                                                                                                     \
        ASSERT_NOT_NULL(wrapper, "wrapper", "try_some");                                                   \
        if( WRAPPER_SOME != wrapper->type ) {                                                              \
            switch(wrapper->type) {                                                                        \
                case WRAPPER_NONE:                                                                         \
                    return wrapper;                                                                        \
                case WRAPPER_OK:                                                                           \
                    fprintf(stderr, "Error: try_some(): expected WRAPPER_SOME, ecountered WRAPPER_OK\n");  \
                    break;                                                                                 \
                case WRAPPER_ERR:                                                                          \
                    fprintf(stderr, "Error: try_some(): expected WRAPPER_SOME, ecountered WRAPPER_ERR\n"); \
                    break;                                                                                 \
                default:                                                                                   \
                    fprintf(stderr, "invalid wrapper type\n");                                             \
            }                                                                                              \
            BLAZE;                                                                                         \
            exit(-1);                                                                                      \
        }                                                                                                  \
        _unwrap_raw(wrapper, utype);                                                                       \
    })

// WRAPPER_SOME: exit(-1)
// WRAPPER_NONE: exit(-1)
// WRAPPER_OK:   _unwrap_wrapper(wrapper, utype)
// WRAPPER_ERR:  wrapper
#define try_ok(wrapper, utype)                                                                          \
    ({                                                                                                  \
        ASSERT_NOT_NULL(wrapper, "wrapper", "try_ok");                                                  \
        if( WRAPPER_OK != wrapper->type ) {                                                             \
            switch(wrapper->type) {                                                                     \
                case WRAPPER_SOME:                                                                      \
                    fprintf(stderr, "Error: try_ok(): expected WRAPPER_OK, ecountered WRAPPER_SOME\n"); \
                    break;                                                                              \
                case WRAPPER_NONE:                                                                      \
                    fprintf(stderr, "Error: try_ok(): expected WRAPPER_OK, ecountered WRAPPER_NONE\n"); \
                    break;                                                                              \
                case WRAPPER_ERR:                                                                       \
                    return wrapper;                                                                     \
                default:                                                                                \
                    fprintf(stderr, "invalid wrapper type\n");                                          \
            }                                                                                           \
            BLAZE;                                                                                      \
            exit(-1);                                                                                   \
        }                                                                                               \
        _unwrap_raw(wrapper, utype);                                                                    \
    })

#endif // _WRAPPER_H_
#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <stdbool.h>

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

#endif // _WRAPPER_H_
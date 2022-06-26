#ifndef _OPTION_H_
#define _OPTION_H_

#include <stdbool.h>

typedef void* Option_t;

bool is_some(Option_t pOption);
bool is_none(Option_t pOption);

#define Option(...) Option_t
#define Some(p) ((Option_t)p)
#define None NULL

#endif // _OPTION_H_
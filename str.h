#ifndef _STR_H_
#define _STR_H_

#include <string.h>

#define MAX_STR_LEN 1000
#define STRLEN(s) strnlen(s, MAX_STR_LEN)
#define STRCMP(s1, s2) strncmp(s1, s2, MAX_STR_LEN)
#define STRCPY(dest, src) strncpy(dest, src, STRLEN(src))

#endif // _STR_H_
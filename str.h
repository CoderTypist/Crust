#ifndef _STR_H_
#define _STR_H_

#include <sys/types.h>

#define MAX_LEN_STR 200

// strlen
size_t unsafe_strlen(char* pStr);
size_t safe_strnlen(char* pStr, size_t maxlen);
// strcpy
char* unsafe_strcpy(char* pDest, char* pSrc);
char* safe_strncpy(char* pDest, char* pSrc, size_t n);
// strcat
char* unsafe_strcat(char *pDest, char* pSrc);
char* safeish_strncat(char* pDest, char* pSrc, size_t n);
char* safe_strncat(char* pDest, char* pSrc, size_t maxlen, size_t n);

#endif // _STR_H_

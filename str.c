#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "str.h"


// Unsafe because MAX_LEN_STR bytes are read regardless of the actual size of pStr
// Even if strnlen() goes passed the memory allocated for pStr, no memory is manipulated
size_t unsafe_strlen(char* pStr) {

    ASSERT_NOT_NULL(pStr, "pStr", "safe_strlen");

    size_t len = strnlen(pStr, MAX_LEN_STR);

    if( '\0' != pStr[len] ) {
        fprintf(stderr, "\tError: safe_strlen(): either...\n");
        fprintf(stderr, "\t\t- pStr is not NULL terminated\n");
        fprintf(stderr, "\t\t- length of pStr exceeds MAX_LEN_STR\n");
        TRACE;
        exit(-1);
    }

    return len;
}

size_t safe_strnlen(char* pStr, size_t maxlen) {

    ASSERT_NOT_NULL(pStr, "pStr", "safe_strnlen");
    ASSERT_POSITIVE(maxlen, "maxlen", "safe_strnlen");

    size_t len = strnlen(pStr, maxlen);

    if( '\0' != pStr[len] ) {
        fprintf(stderr, "\tError: safe_strnlen(): either...\n");
        fprintf(stderr, "\t\t- pStr is not NULL terminated\n");
        fprintf(stderr, "\t\t- length of pStr exceeds MAX_LEN_STR\n");
        TRACE;
        exit(-1);
    }

    return len;
}

// Unsafe because up to MAX_LEN_STR bytes are copied regardless of pDest size
// Unsafe because len of pSrc can be exceeded if not NULL terminated
// A buffer overflow would be limited to MAX_LEN_STR bytes
// Setting MAX_LEN_STR to a smaller value limits the effect of a buffer overflow, but limits flexibility
char* unsafe_strcpy(char* pDest, char* pSrc) {

    ASSERT_NOT_NULL(pDest, "pDest", "unsafe_strcpy");
    ASSERT_NOT_NULL(pSrc, "pSrc", "unsafe_strcpy");

    size_t lenSrc = safe_strlen(pSrc);   // ensures pSrc is NULL terminated
    pDest[lenSrc] = '\0'; // if MAX_LEN_STR == lenSrc
    return strncpy(pDest, pSrc, lenSrc);
}

// Safe because maximum number of bytes to copied is specified
char* safe_strncpy(char* pDest, char* pSrc, size_t n) {

    ASSERT_NOT_NULL(pDest, "pDest", "safe_strncpy");
    ASSERT_NOT_NULL(pSrc, "pSrc", "safe_strncpy");
    ASSERT_POSITIVE(n, "n", "safe_strncpy");

    size_t lenSrc = safe_strnlen(pSrc, n);   // ensures pSrc is NULL terminated
    pDest[lenSrc] = '\0'; // if MAX_LEN_STR == lenSrc
    return strncpy(pDest, pSrc, lenSrc);
}

// Unsafe because up to MAX_LEN_STR bytes are copied regardless of pDest size
// Unsafe because len of pSrc can be exceeded if not NULL terminated
char* unsafe_strcat(char *pDest, char* pSrc) {

    ASSERT_NOT_NULL(pDest, "pDest", "unsafe_strcat");
    ASSERT_NOT_NULL(pSrc, "pSrc", "unsafe_strcat");

    size_t lenSrc = unsafe_strlen(pSrc);

    return strncat(pDest, pSrc, lenSrc);
}

// Unsafe because up to n bytes are copied regardless of pDest size
// Safer because max bytes to read from pSrc is specifiec
char* safeish_strncat(char* pDest, char* pSrc, size_t n) {

    ASSERT_NOT_NULL(pDest, "pDest", "safeish_strncat");
    ASSERT_NOT_NULL(pSrc, "pSrc", "safeish_strncat");
    ASSERT_POSITIVE(n, "n", "safeish_strncat");

    size_t lenDest = unsafe_strlen(pDest);
    size_t lenSrc = safe_strnlen(pSrc, n);

    return strncat(pDest, pSrc, n);
}

// Safe because max bytes to read from pSrc is specified
// Safe because max size of pDest is specified
// It is assumed pDest is of size maxlen+1
char* safe_strncat(char* pDest, char* pSrc, size_t maxlen, size_t n) {

    ASSERT_NOT_NULL(pDest, "pDest", "safe_strncat");
    ASSERT_NOT_NULL(pSrc, "pSrc", "safe_strncat");
    ASSERT_POSITIVE(maxlen, "maxlen", "safe_strncat");
    ASSERT_POSITIVE(n, "n", "safe_strncat");

    if( n > maxlen ) {
        fprintf(stderr, "\tError: safe_strncat(): n > maxlen\n");
        TRACE;
        exit(-1);
    }

    size_t lenDest = safe_strnlen(pDest, maxlen);
    size_t lenSrc = safe_strnlen(pSrc, n);

    if( (lenDest+lenSrc) > maxlen ) {
        fprintf(stderr, "\tError: safe_strncat(): (lenDest+lenSrc) > n\n");
        TRACE;
        exit(-1);
    }

    // check to see if pDest even has a NULL byte
    // find the index of the first NULL byte
    // check if n >= ( maxlen - indexOfFirstNULLByte )

    return NULL;
}
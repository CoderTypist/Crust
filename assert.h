#ifndef _ASSERT_H_
#define _ASSERT_H_

#define TRACE fprintf(stderr, "\t@%s:%d\n", __FILE__, __LINE__)

void assert_alloc(void* pVoid, const char* strVar, const char* strFunction, const char* strAlloc);
#define ASSERT_ALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, NULL)
#define ASSERT_MALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, "malloc")
#define ASSERT_CALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, "calloc")
#define ASSERT_REALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, "realloc")

void assert_not_null(void* pVoid, const char* strVar, const char* strFunction);
#define ASSERT_NOT_NULL(p, strVar, strFunction) assert_not_null((void*)p, strVar, strFunction)

// By using a macro, we avoid having to worry about numbers of various types/sizes
#define ASSERT_NON_NEGATIVE(i, strVar, strFunction)                   \
    ({                                                                \
        if( i < 0 ) {                                                 \
            fprintf(stderr, "\tError: ASSERT_NON_NEGATIVE: i < 0\n"); \
            TRACE;                                                    \
            exit(-1);                                                 \
        }                                                             \
        i;                                                            \
    })

#define ASSERT_POSITIVE(i, strVar, strFunction)                       \
    ({                                                                \
        if( i <= 0 ) {                                                \
            fprintf(stderr, "\tError: ASSERT_POSITIVE: i < 0\n");     \
            TRACE;                                                    \
            exit(-1);                                                 \
        }                                                             \
        i;                                                            \
    })

#endif // _ASSERT_H_
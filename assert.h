#ifndef _ASSERT_H_
#define _ASSERT_H_

void assert_alloc(void* pVoid, const char* strVar, const char* strFunction, const char* strAlloc);
#define ASSERT_ALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, NULL)
#define ASSERT_MALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, "malloc")
#define ASSERT_CALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, "calloc")
#define ASSERT_REALLOC(p, strVar, strFunction) assert_alloc((void*)p, strVar, strFunction, "realloc")

void assert_not_null(void* pVoid, const char* strVar, const char* strFunction);
#define ASSERT_NOT_NULL(p, strVar, strFunction) assert_not_null((void*)p, strVar, strFunction)

#endif // _ASSERT_H_
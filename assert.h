#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

void assert_malloc(void* pVoid, const char* strFunction);
#define ASSERT_MALLOC(p, function) assert_malloc((void*)p, function);

#endif // _ASSERT_H_
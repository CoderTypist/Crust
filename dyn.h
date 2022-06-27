#ifndef _DYN_H_
#define _DYN_H_

#include <stdbool.h>

void* dyn_str(const char* pStr);
void* dyn_var(void* pVoid, int iSize);

/* # converts the argument to a string literal
 * 
 * if the argument starts with a double-quote, a string literal was passed
 * if the argument does not start with a double-quote, a string literal was not passed
 * 
 * if the argument is a string literal, do not use & to get the address
 * if the argument is not a string literal, use & to get the address
 */ 
#define dyn(var) ( ((#var)[0] == '\"') ? dyn_str(var) : dyn_var((void*)&var, sizeof(var)) )

#endif // _DYN_H_
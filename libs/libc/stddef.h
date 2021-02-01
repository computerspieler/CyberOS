#ifndef _STDDEF_H_
#define _STDDEF_H_

#include "stdint.h"

typedef enum bool bool;

typedef int ptrdiff_t;
typedef uint32_t size_t;
typedef uint32_t wchar_t;

enum bool
{
	true = 1,
	false = 0
};

#define NULL (void*) 0
#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

#endif

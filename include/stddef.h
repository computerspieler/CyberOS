#ifndef _STDDEF_H_
#define _STDDEF_H_

typedef enum bool bool;
typedef unsigned char  		uint8_t;
typedef unsigned short 		uint16_t;
typedef unsigned int   		uint32_t;
typedef unsigned long long	uint64_t;

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

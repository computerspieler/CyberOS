#ifndef __STRING_H__
#define __STRING_H__

#include "stddef.h"

void* memchr(const void* str, uint8_t c, size_t count);
int memcmp(const void* str1, const void* str2, size_t count);
void* memcpy(void* dest, const void* src, size_t count);
void* memmove(void* dest, const void* src, size_t count);
void* memset(void* str, uint8_t c, size_t count);

size_t strlen(const char* str);
char* strchr(const char* str, uint8_t c);
char* strrchr(const char* str, uint8_t c);

int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t count);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t count);
size_t strcspn(const char* str1, const char* str2);
char* strpbrk(const char* str1, const char* str2);
size_t strspn(const char* str1, const char* str2);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t count);
char* strstr(const char* haystack, const char* needle);
char* strtok(const char* str, const char* delim);

#ifndef COMPILE_LIBC
	char* strtok_last_string;
#endif

#endif
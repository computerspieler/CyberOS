#include "string.h"

void* memchr(const void* str, uint8_t c, size_t count)
{
	int i;
	uint8_t* str_converted = str;

	for(i = 0; str_converted[i] != 0; i++)
		if(str_converted[i] == c)
			return (str_converted + i);

	return NULL;
}

int memcmp(const void* str1, const void* str2, size_t count)
{
	return strncmp(str1, str2, count);
}

void* memcpy(void* dest, const void* src, size_t count)
{
	return (void*) strncpy(dest, src, count);
}

void* memmove(void* dest, const void* src, size_t count)
{
	return memcpy(dest, src, count);
}

void* memset(void* str, uint8_t c, size_t count)
{
	int i;
	uint8_t* str_converted = str;

	for(i = 0; i < count; i++)
		str_converted[i] = c;

	return str;
}
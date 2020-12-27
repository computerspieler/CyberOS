#include "string.h"

size_t strlen(const char* str)
{
	size_t length = 0;

	while(str[length] != 0)
		length ++;

	return length;
}

char* strchr(const char* str, uint8_t c)
{
	int i;

	for(i = 0; str[i] != 0; i++)
		if(str[i] == c)
			return (str + i);

	return NULL;
}

char* strrchr(const char* str, uint8_t c)
{
	int i;
	size_t str_length = strlen(str);

	for(i = str_length; i > 0; i--)
		if(str[i] == c)
			return (str + i);

	return NULL;
}

int strcmp(const char* str1, const char* str2)
{
	int i;

	for(i = 0; str1[i] == str2[i]; i++)
		if(str1[i] == 0)
			break;

	return str1[i] - str2[i];
}

int strncmp(const char* str1, const char* str2, size_t count)
{
	int i;

	for(i = 0; i < count; i++)
		if(str1[i] != str2[i])
			return str1[i] - str2[i];

	return 0;		
}

char* strcpy(char* dest, const char* src)
{
	return strncpy(dest, src, strlen(src));
}

char* strncpy(char* dest, const char* src, size_t count)
{
	int i;

	if(dest < src)
	{
		for(i = 0; i < count; i++)
			dest[i] = src[i];
	}
	else if(dest > src)
	{
		for(i = count; i > 0; i--)
			dest[i] = src[i];
	}

	return dest;
}

size_t strcspn(const char* str1, const char* str2)
{
	int i;
	int j;

	for(i = 0; str1[i] != 0; i++)
	{
		for(j = 0; str2[j] != 0 && str1[i] != str2[j]; j++)
			;

		if(str1[i] == str2[j])
			break;
	}
	return i;
}

char* strpbrk(const char* str1, const char* str2)
{
	size_t first_common_character = strcspn(str1, str2);
	if(str1[first_common_character] == 0)
		return NULL;

	return &str1[first_common_character];
}

size_t strspn(const char* str1, const char* str2)
{
	int i;
	int j;
	size_t begin = strcspn(str1, str2);
	size_t length = 0;
	bool valid_character;

	for(i = begin; str1[i] != 0; i++, length ++)
	{
		valid_character = false;
		for(j = 0; str2[j] != 0 && !valid_character; j++)
			valid_character = (str1[i] == str2[j]);

		if(!valid_character)
			break;
	}

	return length;
}

char* strcat(char* dest, const char* src)
{
	int i;
	size_t dest_original_length = strlen(dest);

	for(i = 0; src[i] != 0; i++)
		dest[i + dest_original_length] = src[i];

	return dest;
}

char* strncat(char* dest, const char* src, size_t count)
{
	int i;
	size_t dest_original_length = strlen(dest);

	for(i = 0; i < count; i++)
		dest[i + dest_original_length] = src[i];

	return dest;
}

char* strstr(const char* haystack, const char* needle)
{
	int i;
	int j;
	bool found = false;

	for(i = 0; haystack[i] != 0; i++)
	{
		found = true;
		for(j = 0; needle[j] != 0 && found; j++)
			found = (needle[j] == haystack[i + j]);

		if(found)
			break;
	}

	if(haystack[i] == 0)
		return NULL;
	
	return &haystack[i];
}

char* strtok(const char* str, const char* delim)
{
	size_t delim_length = strlen(delim);
	char* delim_instance;
	extern char* strtok_last_string;

	if(str == NULL)
		str = strtok_last_string;

	if(str == NULL)
		return NULL;

	delim_instance = strstr(str, delim);

	if(delim_instance != NULL)
	{
		delim_instance[0] = NULL;
		strtok_last_string = &delim_instance[delim_length];
	}
	else
		strtok_last_string = NULL;

	return str;
}
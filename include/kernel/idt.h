#ifndef _IDT_H_
#define _IDT_H_

#include "typedef.h"

typedef u64 IDT_Entry;
typedef struct IDT_Descriptor IDT_Descriptor;

struct IDT_Descriptor
{
	u16 size;
	IDT_Entry* address;
} __attribute__ ((packed));

IDT_Entry IDT_create_entry(u16 selector, u32 offset, u8 flags);

#endif
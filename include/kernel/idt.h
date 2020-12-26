#ifndef _IDT_H_
#define _IDT_H_

#include "typedef.h"

#define NB_IDT_ENTRIES 256

typedef u64 IDT_Entry;
typedef struct IDT_Descriptor IDT_Descriptor;

struct IDT_Descriptor
{
	u16 size;
	IDT_Entry* address;
} __attribute__ ((packed));

#define IDT_PUSH_DESCRIPTOR(descriptor) \
	asm volatile("lidt (%0)" : : "r" (descriptor))

IDT_Entry IDT_create_entry(u16 selector, u32 offset, u8 flags);

#endif
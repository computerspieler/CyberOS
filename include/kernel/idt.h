#ifndef _IDT_H_
#define _IDT_H_

#include "typedef.h"

#define NB_IDT_ENTRIES 256

typedef struct IDT_Entry IDT_Entry;
typedef struct IDT_Descriptor IDT_Descriptor;

struct IDT_Entry
{
	u16 offset_low;
	u16 selector;
	u8 empty;
	u8 flags;
	u16 offset_high;
} __attribute__ ((packed));

struct IDT_Descriptor
{
	u16 size;
	IDT_Entry* address;
} __attribute__ ((packed));

#define IDT_PUSH_DESCRIPTOR(descriptor) \
	asm volatile("lidt (%0)" : : "r" (descriptor))

IDT_Entry IDT_create_entry(u16 selector, u32 offset, u8 flags);

#endif
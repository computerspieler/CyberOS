#ifndef _GDT_H_
#define _GDT_H_

#include "typedef.h"

typedef struct GDT_Entry GDT_Entry;
typedef struct GDT_Descriptor GDT_Descriptor;

struct GDT_Entry 
{
	u16 limit_low;
	u32 base_low: 24;
	u8 access;
	u8 limit_high : 4;
	u8 flags : 4;
	u8 base_high;
} __attribute__ ((packed));

struct GDT_Descriptor
{
	u16 size;
	GDT_Entry* address;
} __attribute__ ((packed));

#define GDT_FETCH_DESCRIPTOR(descriptor) \
	asm volatile("sgdt (%0)" : : "r" (descriptor))

#define GDT_PUSH_DESCRIPTOR(descriptor) \
	asm volatile("lgdt (%0)" : : "r" (descriptor))

GDT_Entry GDT_create_entry(u32 base_address, u32 limit, u8 flags, u8 access);

#endif

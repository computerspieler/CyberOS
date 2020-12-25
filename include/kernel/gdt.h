#ifndef _GDT_H_
#define _GDT_H_

#include "typedef.h"

typedef u64 GDT_Entry;
typedef struct GDT_Descriptor GDT_Descriptor;

struct GDT_Descriptor
{
	u16 size;
	GDT_Entry* address;
} __attribute__ ((packed));

GDT_Entry GDT_create_entry(u32 base_address, u32 limit, u8 flags, u8 access);

void extract_actual_gdt(GDT_Descriptor* ptr);

#endif

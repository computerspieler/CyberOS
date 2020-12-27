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

#define GDT_PAGE_SIZE 4096

#define GDT_FLAGS_PAGE_BLOCK		1 << 3
#define GDT_FLAGS_32_BITS_SELECTOR	1 << 2

#define GDT_ACCESS_READ_WRITE		1 << 1
#define GDT_ACCESS_CONFORM			1 << 2
#define GDT_ACCESS_CODE_SELECTOR	1 << 3
#define GDT_ACCESS_DESCRIPTOR		1 << 4
#define GDT_ACCESS_PRIVILEGE(x)		x & 0x3 << 5
#define GDT_ACCESS_PRESENT			1 << 7

#define GDT_FETCH_DESCRIPTOR(descriptor) \
	asm volatile("sgdt (%0)" : : "r" (descriptor))

#define GDT_PUSH_DESCRIPTOR(descriptor) \
	asm volatile("lgdt (%0)" : : "r" (descriptor))

GDT_Entry GDT_create_entry(u32 base_address, u32 limit, u8 flags, u8 access);
GDT_Entry GDT_create_code_selector(u32 base_address, u32 limit, u8 flags, u8 privilege);
GDT_Entry GDT_create_data_selector(u32 base_address, u32 limit, u8 flags, u8 privilege);

#endif

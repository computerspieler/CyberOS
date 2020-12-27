#ifndef _GDT_H_
#define _GDT_H_

#include <stddef.h>

typedef struct GDT_Entry GDT_Entry;
typedef struct GDT_Descriptor GDT_Descriptor;

struct GDT_Entry 
{
	uint16_t limit_low;
	uint32_t base_low: 24;
	uint8_t access;
	uint8_t limit_high : 4;
	uint8_t flags : 4;
	uint8_t base_high;
} __attribute__ ((packed));

struct GDT_Descriptor
{
	uint16_t size;
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

GDT_Entry GDT_create_entry(uint32_t base_address, uint32_t limit, uint8_t flags, uint8_t access);
GDT_Entry GDT_create_code_selector(uint32_t base_address, uint32_t limit, uint8_t flags, uint8_t privilege);
GDT_Entry GDT_create_data_selector(uint32_t base_address, uint32_t limit, uint8_t flags, uint8_t privilege);

#endif
